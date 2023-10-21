//
// Created by jmartens on 17.10.2023.
//

#ifndef GALAXIS_GALAXIS_GAME_MODEL_H
#define GALAXIS_GALAXIS_GAME_MODEL_H

#include <cstdio>
#include "subject.h"

enum ViewUpdateMessage {
    Coordinates, SearchResult, ShipCount, Active
};

class GalaxisGameModel : public Subject {
public:
    uint8_t getLastSearchResult() const;

    void setLastSearchResult(uint8_t lastSearchResult);

    uint8_t getX() const;

    void setCoordinates(uint8_t x, uint8_t y);

    uint8_t getY() const;

    uint8_t getShipCount() const;

    void setShipCount(uint8_t shipCount);

    uint8_t getMe() const;

    void setMe(uint8_t me);

    uint8_t getCurrent() const;

    void setCurrent(uint8_t current);

private:
    uint8_t _me = 0;
    uint8_t _current = 0xff;
    uint8_t _x = 0;
    uint8_t _y = 0;
    uint8_t _shipCount = 0;
    uint8_t _lastSearchResult = 0xfa;
    bool _active = false;
public:
    bool isActive() const;
};


#endif //GALAXIS_GALAXIS_GAME_MODEL_H
