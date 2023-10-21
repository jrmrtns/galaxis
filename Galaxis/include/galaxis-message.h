//
// Created by jmartens on 09.10.2023.
//

#ifndef GALAXIS_GALAXIS_MESSAGE_H
#define GALAXIS_GALAXIS_MESSAGE_H

enum MessageType {
    PAIRING, PAIRING_RESPONSE, REQUEST, RESPONSE
};

enum Command {
    SEARCH, NEXT, GAME_OVER
};

typedef struct GalaxisMessage {
    uint8_t msgType;
    uint8_t command;
    uint8_t receiver;
    uint8_t param1;
    uint8_t param2;
} GalaxisMessage;

typedef struct PairingMessage {
    uint8_t msgType;
    uint8_t id;
    uint8_t macAddr[6];
    uint8_t channel;
} PairingMessage;

#endif //GALAXIS_GALAXIS_MESSAGE_H
