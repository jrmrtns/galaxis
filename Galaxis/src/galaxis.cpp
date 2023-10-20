//
// Created by jmartens on 17.04.2023.
//

#include <memory>
#include "galaxis.h"

Galaxis::Galaxis(int count, gameType gameType, bool time_limited) {
    _playerCount = count;
    _gameType = gameType;
    _time_limited = time_limited;

    _gameState = gameState::idle;
    auto board = std::make_shared<Board>();

    for (int i = 0; i < count; ++i) {
        auto *player = new Player(i, board);
        _players.push_back(player);
        if (gameType == gameType::multi_board)
            board = std::make_shared<Board>();
    }
}

uint8_t Galaxis::guess(uint8_t x, uint8_t y) {
    Player *current = _players.at(_currentPlayer);
    uint8_t result = current->makeMove(x, y);

    if (result == 0xfd) {
        _gameState = gameState::gameOver;
        result = 0xff;
    }
    return result;
}

void Galaxis::dumpCurrent() {
    Player *current = _players.at(_currentPlayer);
    current->dump();
}

Galaxis::~Galaxis() {
    for (Player *player: _players) {
        delete player;
    }
    _players.clear();
}

int Galaxis::getPlayerCount() const {
    return _playerCount;
}

int Galaxis::getCurrentPlayer() const {
    return _currentPlayer;
}

gameState Galaxis::getGameState() const {
    return _gameState;
}

void Galaxis::next(uint64_t elapsed) {
    _currentPlayer++;
    _time_limit = elapsed + MAX_TIME * 1000 * 1000;

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

const std::vector<Ship *> &Galaxis::get_ships_by_player(uint8_t player) {
    return _players.at(player)->getHiddenShips();
}

void Galaxis::setTimeLimit(uint64_t timeLimit) {
    _time_limit = timeLimit + (MAX_TIME + 5) * 1000 * 1000;
}
