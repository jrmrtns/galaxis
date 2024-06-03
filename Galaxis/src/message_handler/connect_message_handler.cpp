//
// Created by jmartens on 03.06.2024.
//

#include "message_handler/connect_message_handler.h"

void ConnectMessageHandler::handle(std::shared_ptr<GalaxisGameModel> &galaxisGameModel, GalaxisMessage &message) {
    galaxisGameModel->setMe(message.param2);
    galaxisGameModel->setConnected(message.param1);
    if (galaxisGameModel->isActive()) {
        galaxisGameModel->setHint(START_MESSAGE);
    }
    else {
        String text = PLAYER;
        text+= playerNames[galaxisGameModel->getMe()];
        text+= "\n";
        text += WAITING_FOR_PLAYER;
        if (galaxisGameModel->getCurrent() >= MAX_PLAYERS || galaxisGameModel->getCurrent() < 0)
            text += "Error";
        else
            text += playerNames[galaxisGameModel->getCurrent()];
        galaxisGameModel->setHint(text.c_str());
    }

}
