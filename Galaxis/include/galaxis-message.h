//
// Created by jmartens on 09.10.2023.
//

#ifndef GALAXIS_GALAXIS_MESSAGE_H
#define GALAXIS_GALAXIS_MESSAGE_H

#include <cstdint>

enum MessageType {
    PAIRING, PAIRING_RESPONSE, REQUEST, RESPONSE
};

enum Command : uint8_t {
    CONNECT, START, SEARCH, NEXT, GAME_OVER, NEW_GAME, CLIENT_CONNECTED, ERROR
};

typedef struct GalaxisMessage {
    uint8_t msgType;
    Command command;
    uint8_t id;
    uint8_t param1;
    uint8_t param2;
} GalaxisMessage;

#endif //GALAXIS_GALAXIS_MESSAGE_H
