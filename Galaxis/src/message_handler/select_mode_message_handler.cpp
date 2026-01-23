#include "message_handler/select_mode_message_handler.h"

void SelectModeMessageHandler::handle(std::shared_ptr<GalaxisGameModel> &galaxisGameModel, GalaxisMessage &message) {
    if (message.param1 == 1) {
        galaxisGameModel->setHiding(true);
    } else {
        galaxisGameModel->setHiding(false);
    }
}
