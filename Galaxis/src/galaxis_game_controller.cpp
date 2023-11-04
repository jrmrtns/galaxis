//
// Created by jmartens on 17.10.2023.
//

#include "galaxis_game_controller.h"

#include <utility>
#include "settings.h"
#include "single_player_game.h"

GalaxisGameController::GalaxisGameController(std::shared_ptr<AbstractGame> galaxisGame, std::shared_ptr<GalaxisGameModel> galaxisModel) {
    _galaxisModel = std::move(galaxisModel);
    _galaxisGame = std::move(galaxisGame);
    _galaxisGame->registerObserver(this);
}

void GalaxisGameController::move(int position) {
    uint32_t p = position % (MAX_X * MAX_Y);
    _galaxisModel->setCoordinates(p / MAX_Y, p % MAX_Y);
}

void GalaxisGameController::btnClick(int position) {
    if (_galaxisModel->isGameOver())
        return;

    uint32_t p = position % (MAX_X * MAX_Y);
    _galaxisGame->makeGuess(_galaxisModel->getMe(), p / MAX_Y, p % MAX_Y);
}

void GalaxisGameController::messageReceived(GalaxisMessage message) {
    if (message.msgType != RESPONSE)
        return;

    if (message.command == SEARCH) {
        if (message.id == _galaxisModel->getMe())
            handleSearchMessage(message);
        else
            handleSearchMessageForParticipants(message);
    }

    if (message.command == NEXT) {
        handleNextMessage(message);
    }

    if (message.command == CONNECTED) {
        handleConnectedMessage(message);
    }

    if (message.command == GAME_OVER) {
        handleGameOver();
    }

    if (message.command == NEW_GAME) {
        reset();
    }
}

void GalaxisGameController::handleSearchMessage(const GalaxisMessage &message) {
    _galaxisModel->setLastSearchResult(message.param1);
    if (message.param1 == 0xff)
    {
        _galaxisModel->setShipCount(_galaxisModel->getShipCount() + 1);
    }
}

void GalaxisGameController::initialize() {
    _galaxisModel->setMe(_galaxisModel->getMe());
    _galaxisModel->setHint(CONNECTING);
}

void GalaxisGameController::handleNextMessage(const GalaxisMessage &message) {
    uint8_t nextUser = message.param1;
    _galaxisModel->setCurrent(nextUser);
}

void GalaxisGameController::handleGameOver() {
    _galaxisModel->setGameOver(true);
}

void GalaxisGameController::handleSearchMessageForParticipants(GalaxisMessage message) {
    if (message.param1 == 0xfe || message.param1 == 0xfd ||  message.param1 == 0xfa ||  message.param1 == 0xf0)
        return;

    String text = PLAYER;
    text += char(0x41 + message.id);
    text += ": ";
    if (message.param1 == 0xff) {
        String counter = "0/0";
        counter[0] = char(0x30 + message.param2);
        counter[2] = char(0x30 + SHIP_COUNT);
        text += counter;
    } else {
        text += message.param1;
    }

    _galaxisModel->setHint(text);
}

void GalaxisGameController::handleConnectedMessage(GalaxisMessage message) {
    _galaxisModel->setConnected(message.param1);
    if (_galaxisModel->isActive())
        _galaxisModel->setHint(START_MESSAGE);
    else
    {
        String text = WAITING_FOR_PLAYER;
        text += char(0x41 + _galaxisModel->getCurrent());
        _galaxisModel->setHint(text.c_str());
    }
}

void GalaxisGameController::reset() {
    _galaxisModel->reset();
}
