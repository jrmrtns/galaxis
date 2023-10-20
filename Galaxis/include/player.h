//
// Created by jmartens on 16.04.2023.
//

#ifndef PICOLAXIS_PLAYER_H
#define PICOLAXIS_PLAYER_H


#include <vector>
#include <memory>
#include "board.h"

class Player {
public:
    Player(int i, std::shared_ptr<Board> board);

    int getId() const;

    void dump();

    std::vector<Ship *> _discoveredShips;

    const std::vector<Ship *> &getHiddenShips() const;

    uint8_t makeMove(uint8_t x, uint8_t y);

    uint8_t getDiscovered();

private:
    int _id;
    std::shared_ptr<Board> _board;
};


#endif //PICOLAXIS_PLAYER_H
