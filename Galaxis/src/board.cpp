//
// Created by jmartens on 15.04.2023.
//

#include "board.h"
#include "settings.h"
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <bitset>

int sgn(int val) {
    return (0 < val) - (val < 0);
}

Board::Board() {
    initialize();
}

void Board::initialize() {
    for (int i = 0; i < SHIP_COUNT; ++i) {
        std::unique_ptr<Ship> ship;
        do {
            ship = std::make_unique<Ship>();
        } while (std::any_of(begin(_ships), end(_ships), [&](const auto& existing) { return *ship == *existing; }));
        _ships.push_back(std::move(ship));
    }
}

Board::~Board() {
    _ships.clear();
}

uint8_t Board::scan(uint8_t x, uint8_t y) {
    uint16_t result = 0;

    for (int i = 0; i < SHIP_COUNT; i++) {
        uint16_t s = find(_ships[i].get(), x, y);
        result = result | s;
    }

    if (result >= 512)
        return 0xff;

    result = countBits(result);

    return result;
}

uint8_t Board::countBits(uint16_t value) {
    return std::bitset<16>(value).count();
}

uint16_t Board::find(Ship *ship, uint16_t x, uint16_t y) {
    if (x == ship->getX() && y == ship->getY()) {
        return (uint16_t) pow(2, 9);
    }

    int deltaX = ship->getX() - x;
    int deltaY = ship->getY() - y;

    if ((deltaX != 0) && (deltaY != 0) && (abs(deltaX) != abs(deltaY))) {
        return 0;
    }

    int a = (sgn(deltaX) + 1) * 3;
    int b = sgn(deltaY) + 1;
    int sum = a + b;
    return (uint16_t) pow(2, sum);
}

void Board::dump() {
    printf("\n\n");
    for (int y = 0; y < MAX_Y; ++y) {
        for (int x = 0; x < MAX_X; ++x) {
            printf("%d\t", scan(x, y));
        }
        printf("\n\n");
    }
    printf("\n\n");
}

Ship *Board::findShip(uint8_t x, uint8_t y) {
    auto it = std::find_if(_ships.begin(), _ships.end(), [x, y](const auto& ship)
    {
        return ship->getX() == x && ship->getY() == y;
    });

    return (it != _ships.end()) ? it->get() : nullptr;
}

std::vector<Ship *> Board::getHiddenShips() const {
    std::vector<Ship*> ships;
    for (const auto& ship : _ships)
    {
        ships.push_back(ship.get());
    }
    return ships;}
