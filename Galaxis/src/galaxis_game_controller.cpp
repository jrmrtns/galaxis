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
    uint32_t p = position % (MAX_X * MAX_Y);
    _galaxisGame->makeGuess(p / MAX_Y, p % MAX_Y);
}

void GalaxisGameController::messageReceived(GalaxisMessage message) {
    if (message.msgType != RESPONSE)
        return;

    if (message.command == SEARCH) {
        handleSearchMessage(message);
    }

    if (message.command == NEXT) {
        handleNextMessage(message);
    }

    if (message.command == GAME_OVER) {
        handleGameOver(message);
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
    _galaxisModel->setCurrent(_galaxisModel->getMe());
}

void GalaxisGameController::handleNextMessage(const GalaxisMessage &message) {
    uint8_t nextUser = message.param1;
    _galaxisModel->setCurrent(nextUser);
}

void GalaxisGameController::handleGameOver(const GalaxisMessage &message) {
    _galaxisModel->setHint("Game Over");
}
