//
// Created by jmartens on 02.06.2024.
//

#ifndef GALAXIS_MESSAGEHANDLER_H
#define GALAXIS_MESSAGEHANDLER_H

#include "galaxis_game_model.h"
#include "galaxis-message.h"
#include <memory>

class MessageHandler {
public:
    virtual ~MessageHandler() = default;
    virtual void handle(std::shared_ptr<GalaxisGameModel> &galaxisGameModel, GalaxisMessage &message) = 0;
};

#endif //GALAXIS_MESSAGEHANDLER_H
