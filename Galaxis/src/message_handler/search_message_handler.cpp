//
// Created by jmartens on 02.06.2024.
//

#include "message_handler/search_message_handler.h"

void SearchMessageHandler::handle(std::shared_ptr<GalaxisGameModel> &galaxisGameModel, GalaxisMessage &message) {
    if (message.id == galaxisGameModel->getMe())
        handleSearchMessage(message, galaxisGameModel);
    else
        handleSearchMessageForParticipants(message, galaxisGameModel);}

void SearchMessageHandler::handleSearchMessage(GalaxisMessage &message, std::shared_ptr<GalaxisGameModel> &model) {
    model->setShipCount(message.id, message.param2);
    model->setLastSearchResult(message.param1);
    model->setHint("");
}

void SearchMessageHandler::handleSearchMessageForParticipants(GalaxisMessage &message, std::shared_ptr<GalaxisGameModel> &model) {
    if (message.param1 == 0xfe || message.param1 == 0xfd || message.param1 == 0xfa || message.param1 == 0xf0)
        return;

    if (message.id >= MAX_PLAYERS || message.id < 0)
        return;

    String text = playerNames[message.id];
    text += ": ";
    if (message.param1 == 0xff) {
        String counter = "0/0";
        counter[0] = char(0x30 + message.param2);
        counter[2] = char(0x30 + SHIP_COUNT);
        text += counter;
    } else {
        text += message.param1;
    }

    model->setShipCount(message.id, message.param2);
    model->setHint(text);
}
