//
// Created by jmartens on 17.10.2023.
//

#include "galaxis_game_controller.h"

#include <utility>
#include "settings.h"
#include "single_player_game.h"

GalaxisGameController::GalaxisGameController(std::shared_ptr<AbstractGame> galaxisGame,
                                             std::shared_ptr<GalaxisGameModel> galaxisModel) {
    _galaxisModel = std::move(galaxisModel);
    _galaxisGame = std::move(galaxisGame);
    _galaxisGame->registerObserver(this);
}

void GalaxisGameController::move(int position) {
    if (_galaxisModel->isSearching())
        return;

    uint32_t p = position % (MAX_X * MAX_Y);
    _galaxisModel->setCoordinates(p / MAX_Y, p % MAX_Y);
}

void GalaxisGameController::btnClick() {
    if (_galaxisModel->isGameOver())
        return;

    if (_galaxisModel->getCurrent() != _galaxisModel->getMe())
        return;

    _galaxisModel->setSearching(true);
}

void GalaxisGameController::messageReceived(GalaxisMessage message) {
    if (message.msgType == PAIRING_RESPONSE){
        if (message.command == CONNECT) {
            handleConnectedMessage(message);
        }
    }

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

    if (message.command == CONNECT) {
        handleConnectedMessage(message);
    }

    if (message.command == GAME_OVER) {
        handleGameOver(message.param1);
    }

    if (message.command == CLIENT_CONNECTED) {
        handleClientConnectedMessage(message);
    }

    if (message.command == NEW_GAME) {
        reset();
    }
}

void GalaxisGameController::handleSearchMessage(const GalaxisMessage &message) {
    if (message.param1 == 0xff) {
        _galaxisModel->setShipCount(_galaxisModel->getShipCount() + 1);
    }
    _galaxisModel->setLastSearchResult(message.param1);
    _galaxisModel->setHint("");
}

void GalaxisGameController::initialize() {
    _galaxisModel->setMe(_galaxisModel->getMe());
    if (_galaxisModel->isStarted())
        _galaxisModel->setHint(START_MESSAGE);
    else
        if (_galaxisModel->getMe() == 0)
            _galaxisModel->setHint(CONNECTING);
        else
            _galaxisModel->setHint(WAIT_JOIN);
}

void GalaxisGameController::handleNextMessage(const GalaxisMessage &message) {
    uint8_t nextUser = message.param1;
    _galaxisModel->setCurrent(nextUser);
}

void GalaxisGameController::handleGameOver(uint8_t i) {
    _galaxisGame->shutdown();
    _galaxisModel->setGameOver(true);
    _galaxisModel->setWinner(i == _galaxisModel->getMe());
}

void GalaxisGameController::handleSearchMessageForParticipants(GalaxisMessage message) {
    if (message.param1 == 0xfe || message.param1 == 0xfd || message.param1 == 0xfa || message.param1 == 0xf0)
        return;

    if (message.id > MAX_PERIPHERALS || message.id < 0)
        return;

    String text = playerNames[message.id];
    text += ": ";
    if (message.param1 == 0xff) {
        String counter = "0/0";
        counter[0] = char(0x30 + message.param2);
        counter[2] = char(0x30 + SHIP_COUNT);
        text += counter;
    } else {
        text += message.param1;
    }

    _galaxisModel->setParticipantShipCount(message.param2);
    _galaxisModel->setHint(text);
}

void GalaxisGameController::handleConnectedMessage(GalaxisMessage message) {
    _galaxisModel->setMe(message.param2);
    _galaxisModel->setConnected(message.param1);
    if (_galaxisModel->isActive()) {
        _galaxisModel->setHint(START_MESSAGE);
    }
    else {
        String text = PLAYER;
        text+= playerNames[_galaxisModel->getMe()];
        text+= "\n";
        text += WAITING_FOR_PLAYER;
        if (_galaxisModel->getCurrent() > MAX_PERIPHERALS || _galaxisModel->getCurrent() < 0)
            text += "Error";
        else
            text += playerNames[_galaxisModel->getCurrent()];
        _galaxisModel->setHint(text.c_str());

    }
}

void GalaxisGameController::reset() {
    _galaxisModel->reset();
}

void GalaxisGameController::makeGuess(int position) {
    uint32_t p = position % (MAX_X * MAX_Y);
    _galaxisGame->makeGuess(_galaxisModel->getMe(), p / MAX_Y, p % MAX_Y);
}

void GalaxisGameController::handleClientConnectedMessage(GalaxisMessage message) {
    String text = START_MESSAGE;
    text.concat("\n\n");
    text.concat(CONNECTED);
    text.concat(message.param2 + 1);
    _galaxisModel->setHint(text.c_str());
}
