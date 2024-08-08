//
// Created by jmartens on 20.10.2023.
//

#ifndef GALAXIS_ABSTRACTGAME_H
#define GALAXIS_ABSTRACTGAME_H

#include <cstdint>
#include "message_subject.h"

class AbstractGame  : public MessageSubject{
public:
    virtual ~AbstractGame() = default;
    virtual void makeGuess(uint8_t playerId, uint8_t x, uint8_t y) = 0;
    virtual void startGame() = 0;
};

#endif //GALAXIS_ABSTRACTGAME_H
