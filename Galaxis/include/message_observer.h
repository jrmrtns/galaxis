//
// Created by jmartens on 20.10.2023.
//

#ifndef GALAXIS_MESSAGE_OBSERVER_H
#define GALAXIS_MESSAGE_OBSERVER_H

#include "galaxis-message.h"


class MessageObserver {
public:
    virtual ~MessageObserver() = default;
    virtual void messageReceived(GalaxisMessage param) = 0;
};


#endif //GALAXIS_MESSAGE_OBSERVER_H
