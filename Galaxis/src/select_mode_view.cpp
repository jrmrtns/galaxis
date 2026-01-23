#include "select_mode_view.h"
#include "ui.h"
#include "settings.h"
#include "Arduino.h"
#include "screen_manager.h"

SelectModeView::SelectModeView(RotaryEncoder *encoder) : _encoder(encoder) {}

void SelectModeView::show() {
    _selectedMode = 0;
    updateUi();
    lv_scr_load_anim(ui_MainMenu, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

Screen SelectModeView::loop() {
    int position = _encoder->getPosition();
    if (_lastPosition != position) {
        _selectedMode = (uint32_t)abs(position) % 2;
        updateUi();
        _lastPosition = position;
    }

    int button = digitalRead(PIN_ENC_BUTTON);
    if (button != _lastButtonState && ((millis() - _lastButtonPress) > 25)) {
        if (button == HIGH) {
            ScreenManager::setSelectedGameMode(_selectedMode);
            return Screen::CENTRAL_GAME;
        }
        _lastButtonState = button;
        _lastButtonPress = millis();
    }

    return Screen::NO_CHANGE;
}

void SelectModeView::updateUi() {
    lv_label_set_text(ui_MainMenuItem, _selectedMode == 0 ? SELECT_MODE_RANDOM : SELECT_MODE_HIDE);
    lv_label_set_text(ui_MainMenuHint, SELECT_MODE_TITLE);
}
