//
// Created by jmartens on 03.06.2024.
//

#ifndef GALAXIS_NEW_GAME_MESSAGE_HANDLER_H
#define GALAXIS_NEW_GAME_MESSAGE_HANDLER_H

#include "message_handler.h"

class NewGameMessageHandler : public MessageHandler {
public:
    void handle(std::shared_ptr<GalaxisGameModel> &galaxisGameModel, GalaxisMessage &message) override;
};


#endif //GALAXIS_NEW_GAME_MESSAGE_HANDLER_H
