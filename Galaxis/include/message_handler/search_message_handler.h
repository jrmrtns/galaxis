//
// Created by jmartens on 02.06.2024.
//

#ifndef GALAXIS_SEARCHMESSAGEHANDLER_H
#define GALAXIS_SEARCHMESSAGEHANDLER_H

#include "message_handler.h"
#include "galaxis_game_model.h"

class SearchMessageHandler: public MessageHandler {
public:
    void handle(std::shared_ptr<GalaxisGameModel> &galaxisGameModel, GalaxisMessage &message) override;

    static void handleSearchMessage(GalaxisMessage &message, std::shared_ptr<GalaxisGameModel> &model);

    static void handleSearchMessageForParticipants(GalaxisMessage &message, std::shared_ptr<GalaxisGameModel> &model);
};


#endif //GALAXIS_SEARCHMESSAGEHANDLER_H
