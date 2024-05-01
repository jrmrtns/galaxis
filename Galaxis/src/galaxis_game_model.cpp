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

uint8_t GalaxisGameModel::getShipCount() const {
    return _shipCount;
}

void GalaxisGameModel::setShipCount(uint8_t shipCount) {
    if (_shipCount == shipCount)
        return;

    _shipCount = shipCount;
    notifyView(ViewUpdateMessage::ShipCount);
}

uint8_t GalaxisGameModel::getMe() const {
    return _me;
}

void GalaxisGameModel::setMe(uint8_t me) {
    _me = me;
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
    if (_lastSearchResult == lastSearchResult)
        return;
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
    setShipCount(0);
    setLastSearchResult(0xfe);
    setCoordinates(0, 0);
}

uint8_t GalaxisGameModel::getParticipantShipCount() const {
    return _participantShipCount;
}

void GalaxisGameModel::setParticipantShipCount(uint8_t participantShipCount) {
    if (_participantShipCount == participantShipCount)
        return;

    _participantShipCount = participantShipCount;
    notifyView(ViewUpdateMessage::ParticipantShipCount);
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
