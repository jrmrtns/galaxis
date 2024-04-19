//
// Created by jmartens on 15.04.2023.
//

#include "ship.h"
#include "settings.h"
#include <cstdlib>

Ship::Ship(uint16_t x, uint16_t y) : posX(x), posY(y) {}

bool Ship::operator==(const Ship &rhs) const {
    return posX == rhs.posX &&
           posY == rhs.posY;
}

bool Ship::operator!=(const Ship &rhs) const {
    return !(rhs == *this);
}

Ship::Ship() {
    posX = random() % MAX_X;
    posY = random() % MAX_Y;
}

uint16_t Ship::getX() const {
    return posX;
}

uint16_t Ship::getY() const {
    return posY;
}

