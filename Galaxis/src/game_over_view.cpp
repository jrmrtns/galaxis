//
// Created by jmartens on 05.11.2023.
//

#include "game_over_view.h"
#include "ui.h"
#include "settings.h"
#include "noise_maker.h"

extern NoiseMaker *noiseMaker;

Screen GameOverView::loop() {
    int position = _encoder->getPosition();
    if (_lastPosition != position) {
        _lastPosition = position;
    }

    int button = digitalRead(PIN_ENC_BUTTON);
    if (button != _lastButtonState && ((millis() - _lastButtonPress) > _debounceTimeSpan)) {
        if (button == HIGH) {
            ESP.restart();
            return Screen::MENU;
        }
        _lastButtonState = button;
        _lastButtonPress = millis();
    }

    return Screen::NO_CHANGE;
}

void GameOverView::show() {
    lv_scr_load_anim(ui_GameOver, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
    noiseMaker->playWinner();
}

GameOverView::GameOverView(RotaryEncoder *encoder) : _encoder(encoder) {}
