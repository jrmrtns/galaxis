//
// Created by jmartens on 16.04.2023.
//

#include "player.h"
#include "settings.h"

Player::Player(int i, std::shared_ptr<Board> board) {
    _id = i;
    _board = board;
}

uint8_t Player::makeMove(uint8_t x, uint8_t y) {
    uint8_t result = _board->scan(x, y);
    if (result == 0xff) {
        auto s = _board->findShip(x, y);
        for (Ship *ship: _discoveredShips) {
            if (ship == s) {
                return 0xfe;
            }
        }
        _discoveredShips.push_back(s);

        if (_discoveredShips.size() == SHIP_COUNT)
            return 0xfd;
    }
    return result;
}

void Player::dump(){
    _board->dump();
}

int Player::getId() const {
    return _id;
}

uint8_t Player::getDiscovered() {
    return _discoveredShips.size();
}

const std::vector<Ship *> &Player::getHiddenShips() const {
    return _board->getHiddenShips();
}
