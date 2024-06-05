//
// Created by jmartens on 02.07.2023.
//

#ifndef GALAXIS_BLE_SUBJECT_H
#define GALAXIS_BLE_SUBJECT_H

#include <list>
#include "observer.h"

class Subject {
public:
    void registerObserver(Observer *observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer *observer) {
        observers.remove(observer);
    }

    void notifyView(ViewUpdateMessage param) const {
        for (auto observer: observers) observer->update(param);
    }

private:
    std::list<Observer *> observers;
};

#endif //GALAXIS_BLE_SUBJECT_H
