//
// Created by jmartens on 17.10.2023.
//

#include <WString.h>
#include <utility>
#include "galaxis_game_view.h"
#include "ui.h"
#include "settings.h"
#include "view-update-message.h"
#include "noise_maker.h"
#include "sounds.h"

extern lv_obj_t *my_meter;
extern lv_meter_indicator_t *my_indicator;

extern lv_obj_t *your_meter;
extern lv_meter_indicator_t *your_indicator;

extern NoiseMaker *noiseMaker;

GalaxisGameView::GalaxisGameView(RotaryEncoder *encoder, std::shared_ptr<GalaxisGameController> galaxisController,
                                 std::shared_ptr<GalaxisGameModel> galaxisModel) : _encoder(encoder),
                                                                                   _galaxisController(std::move(
                                                                                           galaxisController)),
                                                                                   _galaxisModel(
                                                                                           std::move(galaxisModel)) {
    _galaxisModel->registerObserver(this);
    _nextIdleToneTime = millis() + IDLE_TIME * 1000;
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
        case Started:
            break;
        case Searching:
            startSearching();
            break;
    }
}

void GalaxisGameView::show() {
    updateActive();
    _galaxisController->initialize();
    updateHint();
    updateConnected();
    updateShipCount();
    updateParticipantShipCount();
    lv_scr_load_anim(ui_Game, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

void GalaxisGameView::updateCoordinates() {
    String txt = "  ";
    txt[0] = char(0x41 + _galaxisModel->getX());
    txt[1] = char(0x31 + _galaxisModel->getY());

    lv_label_set_text(ui_Coordinates, txt.c_str());
}

void GalaxisGameView::updateShipCount() {
    lv_meter_set_indicator_start_value(my_meter, my_indicator, 0);
    lv_meter_set_indicator_end_value(my_meter, my_indicator, _galaxisModel->getShipCount() * 25);
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
    if (searchResult == 0xff) {
        txt = "*";
    } else if (searchResult == 0xfe)
        txt = "-";
    else if (searchResult == 0xfa)
        txt = " ";
    else {
        txt[0] = char(0x30 + searchResult);
    }

    lv_label_set_text(ui_SearchResult, txt.c_str());

    playFeedback(searchResult);
}

void GalaxisGameView::playFeedback(uint8_t searchResult) const {
    if (searchResult == 0)
        noiseMaker->appendTones(beep_0, 1);
    if (searchResult == 1)
        noiseMaker->appendTones(beep_1, 2);
    if (searchResult == 2)
        noiseMaker->appendTones(beep_2, 4);
    if (searchResult == 3)
        noiseMaker->appendTones(beep_3, 6);
    if (searchResult == 4)
        noiseMaker->appendTones(beep_4, 8);
    if (searchResult == 0xfe)
        noiseMaker->appendTones(nope, 7);
    if (searchResult == 0xff)
        if (_galaxisModel->getShipCount() < SHIP_COUNT)
            noiseMaker->appendTones(found, 15);
}

Screen GalaxisGameView::loop() {
    int position = _encoder->getPosition();
    if (_lastPosition != position) {
        _galaxisController->move(position);
        _lastPosition = position;
    }

    playIdle();

    int button = digitalRead(PIN_ENC_BUTTON);
    if (button != _lastButtonState && ((millis() - _lastButtonPress) > _debounceTimeSpan)) {
        if (button == HIGH) {
            _galaxisController->btnClick();
        }
        _lastButtonState = button;
        _lastButtonPress = millis();
    }

    if (_galaxisModel->isGameOver()) {
        if (_galaxisModel->isWinner())
            return Screen::WINNER_SCREEN;
        return Screen::GAME_OVER_SCREEN;
    }

    if (_endAnimationTime != 0 && millis() > _endAnimationTime) {
        endSearching();
    }
    return Screen::NO_CHANGE;
}

void GalaxisGameView::playIdle() {
    if (millis() > _nextIdleToneTime && _galaxisModel->isActive()) {
        noiseMaker->appendTones(idle, 3);
        _nextIdleToneTime = millis() + IDLE_TIME * 1000;
    }
}

void GalaxisGameView::updateHint() {
    lv_label_set_text(ui_StatusLabel, _galaxisModel->getHint().c_str());
}

void GalaxisGameView::updateConnected() {
    int opacity = _galaxisModel->isConnected() * 255;
    _ui_opacity_set(ui_Connected, opacity);
}

void GalaxisGameView::updateGameOver() {
    if (_galaxisModel->isGameOver()) {
        if (_galaxisModel->isWinner()) {
            lv_label_set_text(ui_StatusLabel, String(GAME_OVER_WINNER_MESSAGE).c_str());
        } else {
            lv_label_set_text(ui_StatusLabel, String(GAME_OVER_MESSAGE).c_str());
        }
    } else
        lv_label_set_text(ui_StatusLabel, _galaxisModel->getHint().c_str());
}

void GalaxisGameView::updateParticipantShipCount() {
    lv_meter_set_indicator_start_value(your_meter, your_indicator,
                                       100 - (_galaxisModel->getParticipantShipCount() * 25));
    lv_meter_set_indicator_end_value(your_meter, your_indicator, 100);
}

void GalaxisGameView::startSearching() {
    _nextIdleToneTime = millis() + IDLE_TIME * 1000;

    if (!_galaxisModel->isSearching())
        return;

    _endAnimationTime = millis() + 5200;
    lv_obj_set_style_opa(ui_Coordinates, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Coordinates, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_Coordinates, String(GAME_SCANNING_MESSAGE).c_str());
    lv_label_set_text(ui_SearchResult, "");
    lv_label_set_text(ui_StatusLabel, "");
    search_anim_Animation(ui_Coordinates, 0);
    noiseMaker->appendTones(search, 13);
}

void GalaxisGameView::endSearching() {
    _nextIdleToneTime = millis() + IDLE_TIME * 1000;
    _galaxisModel->setSearching(false);
    _endAnimationTime = 0;
    updateCoordinates();

    _galaxisController->makeGuess(_encoder->getPosition());
}
