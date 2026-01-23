#ifndef GALAXIS_SELECT_MODE_MESSAGE_HANDLER_H
#define GALAXIS_SELECT_MODE_MESSAGE_HANDLER_H

#include "message_handler/message_handler.h"

class SelectModeMessageHandler : public MessageHandler {
public:
    void handle(std::shared_ptr<GalaxisGameModel> &galaxisGameModel, GalaxisMessage &message) override;
};

#endif //GALAXIS_SELECT_MODE_MESSAGE_HANDLER_H
