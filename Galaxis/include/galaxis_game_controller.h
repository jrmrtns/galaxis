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
#include <map>

class GalaxisGameController: protected MessageObserver {
public:
    GalaxisGameController(std::shared_ptr<AbstractGame> galaxisGame, std::shared_ptr<GalaxisGameModel> galaxisModel);

    void move(int position);

    void btnClick();

    void makeGuess(int position);

    void initialize();

protected:
    void messageReceived(GalaxisMessage message) override;

private:
    std::shared_ptr<GalaxisGameModel> _galaxisModel;

    std::shared_ptr<AbstractGame> _galaxisGame;
};



#endif //GALAXIS_GALAXIS_GAME_CONTROLLER_H
