//
// Created by jmartens on 17.10.2023.
//

#include "galaxis_game_model.h"
#include "view-update-message.h"

uint8_t GalaxisGameModel::getX() const {
    return _x;
}

uint8_t GalaxisGameModel::getY() const {
    return _y;
}

uint8_t GalaxisGameModel::getShipCount(uint8_t id) const {
    if (id >= MAX_PLAYERS)
        return 0;

    return _shipCount[id];
}

void GalaxisGameModel::setShipCount(uint8_t id, uint8_t shipCount) {
    if (id >= MAX_PLAYERS)
        return;

    _shipCount[id] = shipCount;
    notifyView(ViewUpdateMessage::ShipCount);
}

uint8_t GalaxisGameModel::getMe() const {
    return _me;
}

void GalaxisGameModel::setMe(uint8_t me) {
    _me = me;
    notifyView(ViewUpdateMessage::Active);
}

uint8_t GalaxisGameModel::getCurrent() const {
    return _current;
}

void GalaxisGameModel::setCurrent(uint8_t current) {
    if (current == _current)
        return;

    _current = current;
    notifyView(ViewUpdateMessage::Active);
}

void GalaxisGameModel::setCoordinates(uint8_t x, uint8_t y) {
    _x = x;
    _y = y;
    notifyView(ViewUpdateMessage::Coordinates);
}

uint8_t GalaxisGameModel::getLastSearchResult() const {
    return _lastSearchResult;
}

void GalaxisGameModel::setLastSearchResult(uint8_t lastSearchResult) {
    _lastSearchResult = lastSearchResult;
    notifyView(ViewUpdateMessage::SearchResult);
}

bool GalaxisGameModel::isActive() const {
    return _current == _me;
}

const String &GalaxisGameModel::getHint() const {
    return _hint;
}

void GalaxisGameModel::setHint(const String &hint) {
    if (_hint == hint)
        return;

    _hint = hint;
    notifyView(ViewUpdateMessage::Hint);
}

bool GalaxisGameModel::isConnected() const {
    return _connected;
}

void GalaxisGameModel::setConnected(bool connected) {
    if (_connected == connected)
        return;

    _connected = connected;
    notifyView(ViewUpdateMessage::Connected);
}

bool GalaxisGameModel::isGameOver() const {
    return _gameOver;
}

void GalaxisGameModel::setGameOver(bool gameOver) {
    if (gameOver == _gameOver)
        return;

    _gameOver = gameOver;
    notifyView(ViewUpdateMessage::GameOver);
}

void GalaxisGameModel::reset() {
    setHint("");
    setShipCount(0, 0);
    setLastSearchResult(0xfe);
    setCoordinates(0, 0);
}

bool GalaxisGameModel::isStarted() const {
    return _started;
}

void GalaxisGameModel::setStarted(bool started) {
    if (started == _started)
        return;

    _started = started;
    notifyView(ViewUpdateMessage::Started);
}

bool GalaxisGameModel::isWinner() const {
    return _winner;
}

void GalaxisGameModel::setWinner(bool winner) {
    _winner = winner;
}

bool GalaxisGameModel::isSearching() const {
    return _searching;
}

void GalaxisGameModel::setSearching(bool searching) {
    if (searching == _searching)
        return;

    _searching = searching;
    notifyView(ViewUpdateMessage::Searching);}

GalaxisGameModel::GalaxisGameModel() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        _shipCount[i] = 0;
    }
}

uint8_t GalaxisGameModel::getRound() const {
    return _round;
}

void GalaxisGameModel::setRound(uint8_t round) {
    _round = round;
    notifyView(ViewUpdateMessage::Round);
}
