//
// Created by jmartens on 17.10.2023.
//

#include "galaxis_game_controller.h"
#include <utility>
#include <memory>
#include <map>
#include "settings.h"
#include "message_handler/message_handler.h"
#include "message_handler/search_message_handler.h"
#include "message_handler/start_message_handler.h"
#include "message_handler/next_message_handler.h"
#include "message_handler/connect_message_handler.h"
#include "message_handler/game_over_message_handler.h"
#include "message_handler/client_connected_message_handler.h"
#include "message_handler/new_game_message_handler.h"

std::map<Command, std::shared_ptr<MessageHandler>> messageHandlers = {{Command::SEARCH,           std::make_shared<SearchMessageHandler>()},
                                                                      {Command::START,            std::make_shared<StartMessageHandler>()},
                                                                      {Command::NEXT,             std::make_shared<NextMessageHandler>()},
                                                                      {Command::GAME_OVER,        std::make_shared<GameOverMessageHandler>()},
                                                                      {Command::CLIENT_CONNECTED, std::make_shared<ClientConnectedMessageHandler>()},
                                                                      {Command::NEW_GAME,         std::make_shared<NewGameMessageHandler>()},
                                                                      {Command::CONNECT,          std::make_shared<ConnectMessageHandler>()}};

GalaxisGameController::GalaxisGameController(std::shared_ptr<AbstractGame> galaxisGame,
                                             std::shared_ptr<GalaxisGameModel> galaxisModel) {
    _galaxisModel = std::move(galaxisModel);
    _galaxisGame = std::move(galaxisGame);
    _galaxisGame->registerObserver(this);
}

void GalaxisGameController::move(int position) {
    if (_galaxisModel->isSearching())
        return;

    uint32_t p = position % (MAX_X * MAX_Y);
    _galaxisModel->setCoordinates(p / MAX_Y, p % MAX_Y);
}

void GalaxisGameController::btnClick() {
    if (_galaxisModel->isGameOver())
        return;

    if (!_galaxisModel->isStarted()) {
        _galaxisGame->startGame();
    }

    if (_galaxisModel->getCurrent() != _galaxisModel->getMe())
        return;

    _galaxisModel->setSearching(true);
}

void GalaxisGameController::messageReceived(GalaxisMessage message) {
    if (message.msgType == PAIRING_RESPONSE) {
        if (message.command == CONNECT) {
            MessageHandler *messageHandler = messageHandlers[message.command].get();
            if (messageHandler) {
                messageHandler->handle(_galaxisModel, message);
            }
        }
    }

    if (message.msgType != RESPONSE)
        return;

    MessageHandler *messageHandler = messageHandlers[message.command].get();
    if (messageHandler) {
        messageHandler->handle(_galaxisModel, message);
    }
}

void GalaxisGameController::initialize() {
    _galaxisModel->setMe(_galaxisModel->getMe());
    if (_galaxisModel->isStarted())
        _galaxisModel->setHint(START_MESSAGE);
    else if (_galaxisModel->getMe() == 0)
        _galaxisModel->setHint(CONNECTING);
    else
        _galaxisModel->setHint(WAIT_JOIN);
}

void GalaxisGameController::makeGuess(int position) {
    uint32_t p = position % (MAX_X * MAX_Y);
    _galaxisGame->makeGuess(_galaxisModel->getMe(), p / MAX_Y, p % MAX_Y);
}
