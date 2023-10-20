//
// Created by jmartens on 15.04.2023.
//

#ifndef PICOLAXIS_BOARD_H
#define PICOLAXIS_BOARD_H


#include <cstdint>
#include <vector>
#include "ship.h"

class Board {
public:
    Board();

    ~Board();

    uint8_t scan(uint8_t x, uint8_t y);

    Ship *findShip(uint8_t x, uint8_t y);

    void dump();

    const std::vector<Ship *> &getHiddenShips() const;

private:
    std::vector<Ship *> _ships;

    void initialize();

    static uint8_t countBits(uint16_t number);

    static uint16_t find(Ship *ship, uint16_t x, uint16_t y);
};

#endif //PICOLAXIS_BOARD_H
