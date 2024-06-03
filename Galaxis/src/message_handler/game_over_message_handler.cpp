//
// Created by jmartens on 03.06.2024.
//

#include "message_handler/game_over_message_handler.h"

void GameOverMessageHandler::handle(std::shared_ptr<GalaxisGameModel> &galaxisGameModel, GalaxisMessage &message) {
    galaxisGameModel->setGameOver(true);
    galaxisGameModel->setWinner(message.param1 == galaxisGameModel->getMe());
}
