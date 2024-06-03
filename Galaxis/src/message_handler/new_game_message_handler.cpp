//
// Created by jmartens on 03.06.2024.
//

#include "message_handler/new_game_message_handler.h"

void NewGameMessageHandler::handle(std::shared_ptr<GalaxisGameModel> &galaxisGameModel, GalaxisMessage &message) {
    galaxisGameModel->reset();
}
