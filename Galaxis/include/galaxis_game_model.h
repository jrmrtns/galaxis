//
// Created by jmartens on 17.10.2023.
//

#ifndef GALAXIS_GALAXIS_GAME_MODEL_H
#define GALAXIS_GALAXIS_GAME_MODEL_H

#include <cstdio>
#include "subject.h"
#include "WString.h"

enum ViewUpdateMessage {
    Coordinates, SearchResult, ShipCount, Active, Hint, Connected
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
    uint8_t _current = 0;
    uint8_t _x = 0;
    uint8_t _y = 0;
    uint8_t _shipCount = 0;
    uint8_t _lastSearchResult = 0xfa;
    String _hint = "";
    bool _connected = false;
public:
    bool isConnected() const;

    void setConnected(bool connected);

public:
    const String &getHint() const;

    void setHint(const String hint);

public:
    bool isActive() const;
};


#endif //GALAXIS_GALAXIS_GAME_MODEL_H
