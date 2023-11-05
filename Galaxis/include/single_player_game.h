//
// Created by jmartens on 20.10.2023.
//

#ifndef GALAXIS_SINGLE_PLAYER_GAME_H
#define GALAXIS_SINGLE_PLAYER_GAME_H

#include "abstract-game.h"
#include "galaxis.h"
#include <memory>

class SinglePlayerGame: public AbstractGame {
public:
    explicit SinglePlayerGame();

    void makeGuess(uint8_t playerId, uint8_t x, uint8_t y) override;

    void shutdown() override;

private:
    std::unique_ptr<Galaxis> _galaxis;

    void SendNextPlayerNotification(uint8_t nextPlayer) const;

    void SendGameOverNotification(uint8_t winner) const;

    void SendGuessResponse(uint8_t receiver, uint8_t guessResult, uint8_t discovered) const;
};


#endif //GALAXIS_SINGLE_PLAYER_GAME_H
