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

extern lv_obj_t *meters[MAX_PLAYERS];
extern lv_meter_indicator_t *indicators[MAX_PLAYERS];

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

void GalaxisGameView::update(ViewUpdateMessage param) {
    switch (param) {
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
        case Started:
            startGame();
            break;
        case Searching:
            startSearching();
            break;
        case Round:
            updateRound();
            break;
    }
}

void GalaxisGameView::show() {
    updateActive();
    _galaxisController->initialize();
    updateHint();
    updateConnected();
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        showShipCount(i);
    }
    lv_scr_load_anim(ui_Game, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

void GalaxisGameView::updateCoordinates() {
    String txtX = String(char(0x41 + _galaxisModel->getX()));
    String txtY = String( char(0x31 + _galaxisModel->getY()));

    lv_label_set_text(ui_CoordinatesX, txtX.c_str());
    lv_label_set_text(ui_CoordinatesY, txtY.c_str());
}

void GalaxisGameView::updateShipCount() {
    uint8_t i = getIndicatorIndex();
    showShipCount(i);
}

uint8_t GalaxisGameView::getIndicatorIndex() const {
    if (_galaxisModel->getCurrent() == _galaxisModel->getMe()) {
        return 0;
    } else {
        int index = _galaxisModel->getCurrent() > _galaxisModel->getMe()
                ? _galaxisModel->getCurrent()
                : _galaxisModel->getCurrent() + 1;
        return index % MAX_PLAYERS;
    }
}

void GalaxisGameView::showShipCount(uint8_t i) const {
    if (i >= MAX_PLAYERS)
        return;

    if (i % 2) {
        lv_meter_set_indicator_start_value(meters[i],
            indicators[i],
            100 - (_galaxisModel->getShipCount(_galaxisModel->getCurrent()) * 25));
        lv_meter_set_indicator_end_value(meters[i], indicators[i], 100);
    } else {
        lv_meter_set_indicator_start_value(meters[i], indicators[i], 0);
        lv_meter_set_indicator_end_value(meters[i],
            indicators[i],
            _galaxisModel->getShipCount(_galaxisModel->getCurrent()) * 25);
    }
}

void GalaxisGameView::updateActive() {
    if (_galaxisModel->isActive()) {
        _nextIdleToneTime = millis();
        _ui_state_modify(ui_Game, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
    }
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
    if (searchResult == 0xff)
        if (_galaxisModel->getShipCount(_galaxisModel->getCurrent()) < SHIP_COUNT)
            noiseMaker->playFound();

    noiseMaker->playBeep(searchResult);
}

Screen GalaxisGameView::loop() {
    int position = _encoder->getPosition();
    if (_lastPosition != position) {
        _galaxisController->move(position);
        _lastPosition = position;
    }

    playIdle();

    drawElapsedTime();

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
        noiseMaker->playIdle();
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

void GalaxisGameView::startSearching() {
    resetNextIdleTime();

    if (!_galaxisModel->isSearching())
        return;

    _endAnimationTime = millis() + 5200;
    lv_obj_set_style_opa(ui_Coordinates, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Coordinates, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_Coordinates, String(GAME_SCANNING_MESSAGE).c_str());
    lv_label_set_text(ui_SearchResult, "");
    lv_label_set_text(ui_StatusLabel, "");
    lv_label_set_text(ui_CoordinatesX, "");
    lv_label_set_text(ui_CoordinatesY, "");
    search_anim_Animation(ui_Coordinates, 0);
    noiseMaker->playSearch();
}

void GalaxisGameView::resetNextIdleTime() { _nextIdleToneTime = millis() + IDLE_TIME * 1000; }

void GalaxisGameView::endSearching() {
    resetNextIdleTime();

    _galaxisModel->setSearching(false);
    _endAnimationTime = 0;
    updateCoordinates();
    lv_obj_set_style_opa(ui_Coordinates, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    _galaxisController->makeGuess(_encoder->getPosition());
}

void GalaxisGameView::updateRound() {
    if (!_galaxisModel->isStarted() || _galaxisModel->getRound() == 0)
        return;

    lv_label_set_text(ui_Round, String(_galaxisModel->getRound()).c_str());
}

void GalaxisGameView::drawElapsedTime() {
    if (!_galaxisModel->isStarted())
        return;

    uint32_t elapsed = (millis() - _startTime) / 1000;
    uint32_t minutes = elapsed / 60;
    uint32_t seconds = elapsed % 60;
    String txt = String(minutes) + ":" + (seconds < 10 ? "0" : "") + String(seconds);
    if (txt == _elapsedTime)
        return;

    _elapsedTime = txt;
    lv_label_set_text(ui_ElapsedTime, txt.c_str());
}

void GalaxisGameView::startGame() {
    _startTime = millis();
}
