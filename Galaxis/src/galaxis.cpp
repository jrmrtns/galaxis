//
// Created by jmartens on 17.04.2023.
//

#include <memory>
#include "galaxis.h"

const uint8_t PLAYER_INVALID = 0xf0;
const uint8_t GAME_OVER_RESULT = 0xfd;
const uint8_t MAX_TIME_LIMIT = 5;

Galaxis::Galaxis(int count, gameType gameType, bool time_limited) {
    _playerCount = count;
    _gameType = gameType;
    _time_limited = time_limited;

    _gameState = gameState::idle;
    auto board = std::make_shared<Board>();

    for (int i = 0; i < count; ++i) {
        _players.push_back(std::make_unique<Player>(i, board));
        if (gameType == gameType::multi_board)
            board = std::make_shared<Board>();
    }
}

uint8_t Galaxis::guess(uint8_t playerId, uint8_t x, uint8_t y) {
    if (_currentPlayer != playerId)
        return PLAYER_INVALID;

    uint8_t result = _players[_currentPlayer]->makeMove(x, y);

    if (result == GAME_OVER_RESULT) {
        _gameState = gameState::gameOver;
        result = 0xff;
    }

    if (result != 0xff && result !=  0xfe)
        next(0);

    return result;
}

void Galaxis::dumpCurrent() {
    _players[_currentPlayer]->dump();
}

Galaxis::~Galaxis() {
    _players.clear();
}

int Galaxis::getPlayerCount() const {
    return _playerCount;
}

int Galaxis::getCurrentPlayerId() const {
    return _currentPlayer;
}

gameState Galaxis::getGameState() const {
    return _gameState;
}

void Galaxis::next(uint64_t elapsed) {
    _time_limit = elapsed + MAX_TIME * 1000 * 1000;

    _currentPlayer++;
    if (_currentPlayer >= _playerCount)
        _currentPlayer = 0;
    _gameState = gameState::idle;
}

gameType Galaxis::getGameType() const {
    return _gameType;
}

bool Galaxis::isTimeLimited() const {
    return _time_limited;
}

uint64_t Galaxis::getTimeLimit() const {
    return _time_limit;
}

void Galaxis::tick(uint64_t elapsed) {
    if (isTimeLimited()) {
        if (elapsed > _time_limit) {
            next(elapsed);
        }
    }
}

std::vector<Ship*> Galaxis::get_ships_by_player(uint8_t player) const {
    return _players[player]->getHiddenShips();
}

void Galaxis::setTimeLimit(uint64_t timeLimit) {
    _time_limit = timeLimit + (MAX_TIME + MAX_TIME_LIMIT) * 1000 * 1000;
}

Player *Galaxis::player(uint8_t player) const {
    if (player >= _playerCount)
        return nullptr;

    return _players[player].get();
}
