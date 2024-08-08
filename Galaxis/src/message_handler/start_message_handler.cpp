//
// Created by jmartens on 03.06.2024.
//

#include "message_handler/start_message_handler.h"

void StartMessageHandler::handle(std::shared_ptr<GalaxisGameModel> &galaxisGameModel, GalaxisMessage &message) {
    galaxisGameModel->setStarted(true);
    galaxisGameModel->setRound(message.param1);
}
