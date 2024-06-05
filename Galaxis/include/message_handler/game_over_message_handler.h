//
// Created by jmartens on 03.06.2024.
//

#ifndef GALAXIS_GAME_OVER_MESSAGE_HANDLER_H
#define GALAXIS_GAME_OVER_MESSAGE_HANDLER_H

#include "message_handler.h"

class GameOverMessageHandler: public MessageHandler {
public:
    void handle(std::shared_ptr<GalaxisGameModel> &galaxisGameModel, GalaxisMessage &message) override;
};


#endif //GALAXIS_GAME_OVER_MESSAGE_HANDLER_H
