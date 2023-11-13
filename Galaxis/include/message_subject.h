//
// Created by jmartens on 20.10.2023.
//

#ifndef GALAXIS_MESSAGE_SUBJECT_H
#define GALAXIS_MESSAGE_SUBJECT_H

#include "message_observer.h"
#include <list>
#include "galaxis-message.h"

class MessageSubject {
public:
    void registerObserver(MessageObserver *observer) {
        observers.push_back(observer);
    }

    void removeObserver(MessageObserver *observer) {
        observers.remove(observer);
    }

    void removeAllObservers(){
        observers.clear();
    }

    void notifyObservers(GalaxisMessage param) const {
        for (auto observer: observers) observer->messageReceived(param);
    }

private:
    std::list<MessageObserver *> observers;
};


#endif //GALAXIS_MESSAGE_SUBJECT_H
