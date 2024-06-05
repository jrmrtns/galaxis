//
// Created by jmartens on 03.06.2024.
//

#include "message_handler/next_message_handler.h"

void NextMessageHandler::handle(std::shared_ptr<GalaxisGameModel> &galaxisGameModel, GalaxisMessage &message) {
    uint8_t nextUser = message.param1;
    galaxisGameModel->setCurrent(nextUser);
}
