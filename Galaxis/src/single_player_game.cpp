//
// Created by jmartens on 20.10.2023.
//

#include "single_player_game.h"

SinglePlayerGame::SinglePlayerGame() {
    _galaxis = std::unique_ptr<Galaxis>(new Galaxis(1, single_board, false));
}

void SinglePlayerGame::shutdown() {

}

void SinglePlayerGame::makeGuess(uint8_t playerId, uint8_t x, uint8_t y) {
    uint8_t currentPlayerId = _galaxis->getCurrentPlayerId();
    uint8_t guessResult = _galaxis->guess(playerId, x, y);
    uint8_t discovered = _galaxis->player(currentPlayerId)->getDiscovered();

    SendGuessResponse(currentPlayerId, guessResult, discovered);
    SendNextPlayerNotification(_galaxis->getCurrentPlayerId());
    if (_galaxis->getGameState() == gameOver)
        SendGameOverNotification(currentPlayerId);
}

void SinglePlayerGame::SendGameOverNotification(uint8_t winner) const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = GAME_OVER;
    message.id = 0xff;
    message.param1 = winner;
    notifyObservers(message);
}

void SinglePlayerGame::SendNextPlayerNotification(uint8_t nextPlayer) const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = NEXT;
    message.id = 0xff;
    message.param1 = nextPlayer;
    notifyObservers(message);
}

void SinglePlayerGame::SendGuessResponse(uint8_t receiver, uint8_t guessResult, uint8_t discovered) const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = SEARCH;
    message.id = receiver;
    message.param1 = guessResult;
    message.param2 = discovered;
    notifyObservers(message);
}

