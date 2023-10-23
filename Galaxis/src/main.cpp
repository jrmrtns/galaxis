#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include "RotaryEncoder.h"
#include <ArduinoBLE.h>

#include <memory>
#include "ble_central_game.h"
#include "screen_manager.h"
#include "galaxis_game_model.h"
#include "galaxis_game_view.h"
#include "galaxis_game_controller.h"
#include "settings.h"
#include "single_player_game.h"

//Image by <a href="https://pixabay.com/users/luminas_art-4128746/?utm_source=link-attribution&utm_medium=referral&utm_campaign=image&utm_content=3608029">Lumina Obscura</a> from <a href="https://pixabay.com//?utm_source=link-attribution&utm_medium=referral&utm_campaign=image&utm_content=3608029">Pixabay</a>
RotaryEncoder *encoder = nullptr;
ScreenManager *screenManager = nullptr;
std::shared_ptr<GalaxisGameModel> gameModel;
GalaxisGameView *gameView;
GalaxisGameController *gameController;

int screen_rotation = 1;

static const uint16_t screenWidth = 240;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

void checkPosition() {
    encoder->tick();
}

void initialize_encoder() {
    pinMode(PIN_ENC_BUTTON, INPUT_PULLUP);

    encoder = new RotaryEncoder(PIN_ENC_IN1, PIN_ENC_IN2, RotaryEncoder::LatchMode::TWO03);
    encoder->setPosition((1000 * MAX_X * MAX_Y));

    attachInterrupt(digitalPinToInterrupt(PIN_ENC_IN1), checkPosition, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_IN2), checkPosition, CHANGE);
}

void dispFlushCallback(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *) &color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

void setup() {
    Serial.begin(115200);
    randomSeed(analogRead(A0));

    lv_init();

    initialize_encoder();
    screenManager = new ScreenManager(encoder);

    if (!BLE.begin()) {
        Serial.println("starting Bluetooth® Low Energy module failed!");

        while (1);
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

    //BLECentralGame::getInstance();

    lv_timer_handler();
    delay(2500);

    gameModel = std::make_shared<GalaxisGameModel>();
    randomSeed(1);
    std::shared_ptr<AbstractGame> game = std::make_shared<BLECentralGame>();
    //std::shared_ptr<AbstractGame> game = std::make_shared<SinglePlayerGame>();
    gameController = new GalaxisGameController(game, gameModel);
    gameView = new GalaxisGameView(encoder, gameController, gameModel);
    gameView->show();
}

void loop() {
    lv_timer_handler();
    BLE.poll();
    //delay(5);
    encoder->tick();
    screenManager->tick();
    gameView->tick();
}
