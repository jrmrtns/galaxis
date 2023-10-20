//
// Created by jmartens on 20.10.2023.
//

#include "single_player_game.h"

SinglePlayerGame::SinglePlayerGame() {
    _galaxis = std::unique_ptr<Galaxis>(new Galaxis(1, single_board, false));
}

void SinglePlayerGame::makeGuess(uint8_t x, uint8_t y) {
    GalaxisMessage message;
    message.msgType = RESPONSE;
    message.command = SEARCH;
    message.param1 = _galaxis->guess(x, y);
    _galaxis->dumpCurrent();
    notifyObservers(message);
}

