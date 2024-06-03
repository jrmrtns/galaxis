//
// Created by jmartens on 03.06.2024.
//

#ifndef GALAXIS_CLIENT_CONNECTED_MESSAGE_HANDLER_H
#define GALAXIS_CLIENT_CONNECTED_MESSAGE_HANDLER_H

#include "message_handler.h"

class ClientConnectedMessageHandler: public MessageHandler {
public:
    void handle(std::shared_ptr<GalaxisGameModel> &galaxisGameModel, GalaxisMessage &message) override;
};


#endif //GALAXIS_CLIENT_CONNECTED_MESSAGE_HANDLER_H
