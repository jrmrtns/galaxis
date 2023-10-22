//
// Created by jmartens on 17.10.2023.
//

#ifndef GALAXIS_GALAXIS_GAME_CONTROLLER_H
#define GALAXIS_GALAXIS_GAME_CONTROLLER_H


#include "galaxis_game_model.h"
#include "RotaryEncoder.h"
#include "abstract-game.h"
#include "message_observer.h"
#include <memory>

class GalaxisGameController: protected MessageObserver{
public:
    GalaxisGameController(std::shared_ptr<AbstractGame> galaxisGame, std::shared_ptr<GalaxisGameModel> galaxisModel);

    void move(int position);

    void btnClick(int position);

    void initialize();

protected:
    void messageReceived(GalaxisMessage message) override;

private:
    std::shared_ptr<GalaxisGameModel> _galaxisModel;

    std::shared_ptr<AbstractGame> _galaxisGame;

    void handleSearchMessage(const GalaxisMessage &message);

    void handleNextMessage(const GalaxisMessage &message);

    void handleGameOver(const GalaxisMessage &message);
};


#endif //GALAXIS_GALAXIS_GAME_CONTROLLER_H
