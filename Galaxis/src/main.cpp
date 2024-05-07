#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include "RotaryEncoder.h"
#include <ArduinoBLE.h>
#include "screen_manager.h"
#include "settings.h"
#include "noise_maker.h"
#include "notes.h"

RotaryEncoder *encoder = nullptr;
ScreenManager *screenManager = nullptr;
NoiseMaker *noiseMaker = nullptr;

int screen_rotation = 1;

lv_obj_t *my_meter;
lv_meter_indicator_t *my_indicator;

lv_obj_t *your_meter;
lv_meter_indicator_t *your_indicator;

lv_color_t primary = lv_palette_main(LV_PALETTE_RED);
lv_color_t secondary = lv_palette_main(LV_PALETTE_ORANGE);

static const uint16_t screenWidth = 240;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];

int lastButtonState = HIGH;
uint32_t lastButtonPress = 0;
uint32_t debounceTimeSpan = 25;

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    //Serial.printf(buf);
    Serial.flush();
}
#endif

void checkPosition() {
    encoder->tick();
}

void sleep(bool value) {
    if (value) {
        tft.writecommand(0x10);   // Send command to put the display to sleep.
        delay(150);               // Delay for shutdown time before another command can be sent.
    } else {
        tft.init();               // This sends the wake up command and initialises the display
        delay(50);                // Extra delay to stop a "white flash" while the TFT is initialising.
    }
}

void extendGameView() {
    lv_obj_set_style_text_color(ui_Coordinates, primary, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SearchResult, primary, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_MainMenuItem, primary, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_GameOverItem, primary, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Game, secondary, LV_STATE_CHECKED);

    my_meter = lv_meter_create(ui_Game);
    lv_obj_remove_style(my_meter, nullptr, LV_PART_INDICATOR);
    lv_obj_remove_style(my_meter, nullptr, LV_PART_MAIN);

    lv_obj_center(my_meter);
    lv_obj_set_size(my_meter, 220, 220);

    lv_meter_scale_t *scale = lv_meter_add_scale(my_meter);
    lv_meter_set_scale_ticks(my_meter, scale, 5, 6, 35, lv_color_hex(0x292831));
    lv_meter_set_scale_range(my_meter, scale, 0, 100, 30, 180);

    my_indicator = lv_meter_add_arc(my_meter, scale, 20, primary, 0);

    your_meter = lv_meter_create(ui_Game);
    lv_obj_remove_style(your_meter, nullptr, LV_PART_INDICATOR);
    lv_obj_remove_style(your_meter, nullptr, LV_PART_MAIN);

    lv_obj_center(your_meter);
    lv_obj_set_size(your_meter, 220, 220);

    lv_meter_scale_t *your_scale = lv_meter_add_scale(your_meter);
    lv_meter_set_scale_ticks(your_meter, your_scale, 5, 6, 35, lv_color_hex(0x292831));
    lv_meter_set_scale_range(your_meter, your_scale, 0, 100, 30, 330);

    your_indicator = lv_meter_add_arc(your_meter, your_scale, 20, secondary, 0);
}

void initialize_encoder() {
    pinMode(PIN_ENC_BUTTON, INPUT_PULLUP);

    encoder = new RotaryEncoder(PIN_ENC_IN1, PIN_ENC_IN2, RotaryEncoder::LatchMode::TWO03);
    encoder->setPosition((1000 * MAX_X * MAX_Y));

    attachInterrupt(digitalPinToInterrupt(PIN_ENC_IN1), checkPosition, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_IN2), checkPosition, CHANGE);
}

void dispFlushCallback(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    int32_t w = (area->x2 - area->x1 + 1);
    int32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *) &color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

void setup() {
    Serial.begin(115200);

#ifdef PIN_ENC_GROUND
    pinMode(PIN_ENC_GROUND, OUTPUT);
    digitalWrite(PIN_ENC_GROUND, LOW);
#endif

    lv_init();

    initialize_encoder();
    screenManager = new ScreenManager(encoder);
    noiseMaker = new NoiseMaker();

    if (!BLE.begin()) {
        Serial.println("starting Bluetooth® Low Energy module failed!");

        while (true);
    }

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print );
#endif

    tft.begin();
    tft.setRotation(screen_rotation);

    lv_disp_draw_buf_init(&draw_buf, buf, nullptr, screenWidth * screenHeight / 10);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = dispFlushCallback;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    ui_init();
    extendGameView();

    lv_timer_handler();
    delay(2500);

    ledcSetup(TONE_PWM_CHANNEL, 12000, 9);
    ledcAttachPin(PIN_TONE_OUTPUT, TONE_PWM_CHANNEL);
    //int beep_2[] = {
    //        NOTE_B5, -8, REST, -8,
    //        NOTE_B5, -8, REST, -8,
    //};
    //noiseMaker->playTones(beep_2, 4);

    //ledcSetup(TONE_PWM_CHANNEL, 12000, 9);
    //ledcAttachPin(PIN_TONE_OUTPUT, TONE_PWM_CHANNEL);
    //noiseMaker->playTones(search, 15);
    //noiseMaker->playTones(beep_0, 1);
    //noiseMaker->playMelody(beep_1, 2);
    //noiseMaker->playMelody(beep_2, 4);
    //noiseMaker->playMelody(beep_3, 6);
    //noiseMaker->playMelody(beep_4, 8);

    //noiseMaker->playMelody(found, 15);
    //noiseMaker->playWinner();

    screenManager->show(MENU);
}

void checkButtonState() {
    int button = digitalRead(PIN_ENC_BUTTON);
    if (button != lastButtonState && ((millis() - lastButtonPress) > debounceTimeSpan)) {
        lastButtonState = button;
        lastButtonPress = millis();
    }

    if (button == LOW && lastButtonState == LOW && ((millis() - lastButtonPress) > 3 * 1000)) {
        esp_restart();
    }
}

void loop() {
    checkButtonState();
    lv_timer_handler();
    BLE.poll();
    noiseMaker->loop();
    screenManager->loop();
}
