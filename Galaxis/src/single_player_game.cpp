//
// Created by jmartens on 20.10.2023.
//

#include "single_player_game.h"

SinglePlayerGame::SinglePlayerGame() {
    _galaxis = std::unique_ptr<Galaxis>(new Galaxis(1, single_board, false));
}

void SinglePlayerGame::makeGuess(uint8_t x, uint8_t y) {
    uint8_t currentPlayer = _galaxis->getCurrentPlayer();
    uint8_t guessResult = _galaxis->guess(x, y);
    SendGuessResponse(currentPlayer, guessResult);
    SendNextPlayerNotification(_galaxis->getCurrentPlayer());
    SendGameOverNotification(currentPlayer);
}

void SinglePlayerGame::SendGameOverNotification(uint8_t winner) const {
    GalaxisMessage message;
    message = GalaxisMessage();
    message.msgType = RESPONSE;
    message.command = GAME_OVER;
    message.receiver = 0xff;
    message.param1 = winner;
    notifyObservers(message);
}

void SinglePlayerGame::SendNextPlayerNotification(uint8_t nextPlayer) const {
    GalaxisMessage message;
    message.msgType = RESPONSE;
    message.command = NEXT;
    message.receiver = 0xff;
    message.param1 = nextPlayer;
    notifyObservers(message);
}

void SinglePlayerGame::SendGuessResponse(uint8_t receiver, uint8_t guessResult) const {
    GalaxisMessage message;
    message.msgType = RESPONSE;
    message.command = SEARCH;
    message.receiver = receiver;
    message.param1 = guessResult;
    notifyObservers(message);
}

