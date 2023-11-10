//
// Created by jmartens on 17.10.2023.
//

#include <WString.h>
#include <utility>
#include "galaxis_game_view.h"
#include "ui.h"
#include "settings.h"
#include "view-update-message.h"

extern lv_obj_t * my_meter;
extern lv_meter_indicator_t * my_indicator;

extern lv_obj_t * your_meter;
extern lv_meter_indicator_t * your_indicator;

GalaxisGameView::GalaxisGameView(RotaryEncoder *encoder, std::shared_ptr<GalaxisGameController> galaxisController,
                                 std::shared_ptr<GalaxisGameModel> galaxisModel) : _encoder(encoder),
                                                                                   _galaxisController(std::move(
                                                                                           galaxisController)),
                                                                                   _galaxisModel(
                                                                                           std::move(galaxisModel)) {
    _galaxisModel->registerObserver(this);
}

GalaxisGameView::~GalaxisGameView() {
    _galaxisModel->removeObserver(this);
}

void GalaxisGameView::update(int param) {
    switch ((ViewUpdateMessage) param) {
        case Coordinates:
            updateCoordinates();
            break;
        case SearchResult:
            updateSearchResult();
            break;
        case ShipCount:
            updateShipCount();
            break;
        case Active:
            updateActive();
            break;
        case Hint:
            updateHint();
            break;
        case Connected:
            updateConnected();
            break;
        case GameOver:
            updateGameOver();
            break;
        case MenuItemChanged:
            break;
        case ParticipantShipCount:
            updateParticipantShipCount();
            break;
    }
}

void GalaxisGameView::show() {
    updateActive();
    _galaxisController->initialize();
    updateHint();
    updateConnected();
    updateShipCount();
    lv_scr_load_anim(ui_Game, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

void GalaxisGameView::updateCoordinates() {
    String txt = "   ";
    txt[0] = char(0x41 + _galaxisModel->getX());
    txt[2] = char(0x31 + _galaxisModel->getY());

    lv_label_set_text(ui_Coordinates, txt.c_str());
}

void GalaxisGameView::updateShipCount() {
    String txt = "0/0";
    txt[0] = char(0x30 + _galaxisModel->getShipCount());
    txt[2] = char(0x30 + SHIP_COUNT);

    lv_meter_set_indicator_start_value(my_meter, my_indicator, 0);
    lv_meter_set_indicator_end_value(my_meter, my_indicator, _galaxisModel->getShipCount() * 25);

    lv_label_set_text(ui_ShipCount, txt.c_str());
}

void GalaxisGameView::updateActive() {
    if (_galaxisModel->isActive())
        _ui_state_modify(ui_Game, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
    else
        _ui_state_modify(ui_Game, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
}

void GalaxisGameView::updateSearchResult() {
    uint8_t searchResult = _galaxisModel->getLastSearchResult();
    if (searchResult == 0xf0)
        return;

    String txt = " ";
    if (searchResult == 0xff)
        txt = "X";
    else if (searchResult == 0xfe)
        txt = "-";
    else if (searchResult == 0xfa)
        txt = " ";
    else
        txt[0] = char(0x30 + searchResult);

    lv_label_set_text(ui_SearchResult, txt.c_str());
}

Screen GalaxisGameView::loop() {
    int position = _encoder->getPosition();
    if (_lastPosition != position) {
        _galaxisController->move(position);
        _lastPosition = position;
    }

    int button = digitalRead(PIN_ENC_BUTTON);
    if (button != _lastButtonState && ((millis() - _lastButtonPress) > _debounceTimeSpan)) {
        if (button == HIGH) {
            _galaxisController->btnClick(position);
        }
        _lastButtonState = button;
        _lastButtonPress = millis();
    }

    if (_galaxisModel->isGameOver())
        return Screen::GAME_OVER_SCREEN;

    return Screen::NONE;
}

void GalaxisGameView::updateHint() {
    lv_label_set_text(ui_StatusLabel, _galaxisModel->getHint().c_str());
}

void GalaxisGameView::updateConnected() {
    int opacity = _galaxisModel->isConnected() * 255;
    _ui_opacity_set(ui_Connected, opacity);
}

void GalaxisGameView::updateGameOver() {
    if (_galaxisModel->isGameOver())
        lv_label_set_text(ui_StatusLabel, String(GAME_OVER_MESSAGE).c_str());
    else
        lv_label_set_text(ui_StatusLabel, _galaxisModel->getHint().c_str());
}

void GalaxisGameView::updateParticipantShipCount() {
    lv_meter_set_indicator_start_value(your_meter, your_indicator, 100 - (_galaxisModel->getParticipantShipCount() * 25));
    lv_meter_set_indicator_end_value(your_meter, your_indicator, 100);
}
