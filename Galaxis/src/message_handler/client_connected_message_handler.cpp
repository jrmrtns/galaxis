//
// Created by jmartens on 03.06.2024.
//

#include "message_handler/client_connected_message_handler.h"

void ClientConnectedMessageHandler::handle(std::shared_ptr<GalaxisGameModel> &galaxisGameModel, GalaxisMessage &message) {
    String text = START_MESSAGE;
    text.concat("\n");
    text.concat(CONNECTED);
    text.concat(message.param1);
    galaxisGameModel->setHint(text.c_str());
}
