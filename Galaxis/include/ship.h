//
// Created by jmartens on 15.04.2023.
//

#ifndef PICOLAXIS_SHIP_H
#define PICOLAXIS_SHIP_H

#include <cstdint>

class Ship {
private:
    uint16_t posX = -1;
    uint16_t posY = -1;
public:
    bool operator==(const Ship &rhs) const;

    Ship(uint16_t x, uint16_t y);

    Ship();

    uint16_t getX() const;

    void setX(uint16_t x);

    uint16_t getY() const;

    void setY(uint16_t y);

    bool operator!=(const Ship &rhs) const;
};


#endif //PICOLAXIS_SHIP_H
