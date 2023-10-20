//
// Created by jmartens on 17.10.2023.
//

#include <WString.h>

#include <utility>
#include "galaxis_game_view.h"
#include "ui.h"
#include "settings.h"

GalaxisGameView::GalaxisGameView(RotaryEncoder *encoder, GalaxisGameController *galaxisController,
                                 std::shared_ptr<GalaxisGameModel> galaxisModel) : _encoder(encoder),
                                                                   _galaxisController(galaxisController),
                                                                   _galaxisModel(std::move(galaxisModel)) {
    _galaxisModel->registerObserver(this);
}

GalaxisGameView::~GalaxisGameView() {
    _galaxisModel->removeObserver(this);
}

void GalaxisGameView::update(int param) {
    switch ((UpdateMessage) param) {
        case Coordinates:
            updateCoordinates();
            break;
        case SearchResult:
            updateSearchResult();
            break;
        case ShipCount:
            updateShipCount();
            break;
    }
}

void GalaxisGameView::show() {
    lv_scr_load_anim(ui_Game, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
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

    lv_label_set_text(ui_ShipCount, txt.c_str());
}

void GalaxisGameView::updateSearchResult() {
    uint8_t n = _galaxisModel->getLastSearchResult();
    String txt = " ";
    if (n == 0xff)
        txt = "X";
    else if (n == 0xfe)
        txt = "-";
    else if (n == 0xfa)
        txt = " ";
    else
        txt[0] = char(0x30 + n);

    lv_label_set_text(ui_SearchResult, txt.c_str());
}

void GalaxisGameView::tick() {
    int position = _encoder->getPosition();
    if (_lastPosition != position) {
        _galaxisController->move(position);
        _lastPosition = position;
    }

    int button = digitalRead(PIN_ENC_BUTTON);
    if (button != lastButtonState && ((millis() - lastButtonPress) > debounceTimeSpan)) {
        if (button == HIGH) {
            _galaxisController->btnClick(position);
        }
        lastButtonState = button;
        lastButtonPress = millis();
    }
}

