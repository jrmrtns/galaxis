//
// Created by jmartens on 17.04.2023.
//

#ifndef PICOLAXIS_GALAXIS_H
#define PICOLAXIS_GALAXIS_H

#include "player.h"
#include "game-state.h"
#include <vector>

#define MAX_TIME 60

class Galaxis {
public:
    Galaxis(gameType gameType, bool time_limited);

    virtual ~Galaxis();

    uint8_t guess(uint8_t playerId, uint8_t x, uint8_t y);

    void next(uint64_t elapsed);

    void dumpCurrent();

    uint16_t getPlayerCount() const;

    int getCurrentPlayerId() const;

    Player * player(uint8_t player) const;

    gameState getGameState() const;

    bool isTimeLimited() const;

    gameType getGameType() const;

    void tick(uint64_t elapsed);

    uint8_t join();

    void remove(uint8_t id);

    std::vector<Ship *> get_ships_by_player(uint8_t player) const;

private:
    gameType _gameType;
    int _currentPlayer = 0;
    bool _time_limited = false;
    std::vector<std::unique_ptr<Player>> _players;
    gameState _gameState;
    uint64_t _time_limit = 0;
    std::shared_ptr<Board> _board;
public:
    void setTimeLimit(uint64_t timeLimit);

    uint64_t getTimeLimit() const;
};


#endif //PICOLAXIS_GALAXIS_H
