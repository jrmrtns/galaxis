//
// Created by jmartens on 17.10.2023.
//

#include "galaxis_game_controller.h"

#include <utility>
#include "settings.h"
#include "single_player_game.h"

GalaxisGameController::GalaxisGameController(std::shared_ptr<GalaxisGameModel> galaxisModel) {
    _galaxisModel = std::move(galaxisModel);
    _galaxisGame =  std::unique_ptr<SinglePlayerGame>(new  SinglePlayerGame());
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

void GalaxisGameController::messageReceived(GalaxisMessage param) {
    if (param.msgType != RESPONSE)
        return;

    if (param.command == SEARCH) {
        _galaxisModel->setLastSearchResult(param.param1);
        if (param.param1 == 0xff)
        {
            _galaxisModel->setShipCount(_galaxisModel->getShipCount() + 1);
        }
    }
}
