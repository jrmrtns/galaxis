//
// Created by jmartens on 05.11.2023.
//

#include "settings_view.h"
#include "ui.h"
#include "settings.h"
#include "preferences.h"

extern bool playSound;
extern bool playIdleSound;
extern Preferences preferences;

Screen SettingsView::loop() {
    int position = _encoder->getPosition();
    if (_lastPosition != position) {
        _lastPosition = position;
        setFocus(position);
    }

    int button = digitalRead(PIN_ENC_BUTTON);
    if (button != _lastButtonState && ((millis() - _lastButtonPress) > _debounceTimeSpan)) {
        if (button == HIGH) {
            if (click())
                return Screen::MENU;
        }
        _lastButtonState = button;
        _lastButtonPress = millis();
    }

    return Screen::NO_CHANGE;
}

void SettingsView::show() {
    updateStates();

    lv_scr_load_anim(ui_Settings, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

void SettingsView::updateStates() const {
    if (playSound)
        lv_obj_add_state(ui_shouldPlaySounds, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(ui_shouldPlaySounds, LV_STATE_CHECKED);
    if (playIdleSound)
        lv_obj_add_state(ui_shouldPlayIdle, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(ui_shouldPlayIdle, LV_STATE_CHECKED);
}

SettingsView::SettingsView(RotaryEncoder *encoder) : _encoder(encoder) {}

void SettingsView::setFocus(int position) {
    _focusedElement = position % 3;
    if (_focusedElement == 0) {
        lv_obj_add_state(ui_shouldPlaySounds, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_shouldPlayIdle, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_okButton, LV_STATE_FOCUSED);
    }
    if (_focusedElement == 1) {
        lv_obj_clear_state(ui_shouldPlaySounds, LV_STATE_FOCUSED);
        lv_obj_add_state(ui_shouldPlayIdle, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_okButton, LV_STATE_FOCUSED);
    }
    if (_focusedElement == 2) {
        lv_obj_clear_state(ui_shouldPlaySounds, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_shouldPlayIdle, LV_STATE_FOCUSED);
        lv_obj_add_state(ui_okButton, LV_STATE_FOCUSED);
    }
}

bool SettingsView::click() {
    if (_focusedElement == 0)
        playSound = !playSound;
    if (_focusedElement == 1)
        playIdleSound = !playIdleSound;
    if (_focusedElement == 2) {
        preferences.begin("galaxis", false);
        preferences.putBool("Sound", playSound);
        preferences.putBool("IdleSound", playIdleSound);
        preferences.end();
        return true;
    }
    updateStates();
    return false;
}
