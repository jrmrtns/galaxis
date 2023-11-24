#include "player.h"
#include "settings.h"
#include <algorithm>
#include <utility>

const uint8_t DISCOVERED = 0xff;
const uint8_t REPEATED_SCAN = 0xfe;
const uint8_t ALL_SHIPS_DISCOVERED = 0xfd;

Player::Player(int i, std::shared_ptr<Board> board)
        : _id(i), _board(std::move(board)) {
}

uint8_t Player::makeMove(uint8_t x, uint8_t y) {
    uint8_t result = _board->scan(x, y);
    if (result == DISCOVERED) {
        auto s = _board->findShip(x, y);

        if(std::find(_discoveredShips.begin(), _discoveredShips.end(), s) != _discoveredShips.end())
            return REPEATED_SCAN;
        _discoveredShips.push_back(s);

        if (_discoveredShips.size() == SHIP_COUNT)
            return ALL_SHIPS_DISCOVERED;
    }
    return result;
}

void Player::dump() const {
    _board->dump();
}

int Player::getId() const {
    return _id;
}

uint8_t Player::getDiscovered() const {
    return _discoveredShips.size();
}

std::vector<Ship *> Player::getHiddenShips() const {
    return _board->getHiddenShips();
}