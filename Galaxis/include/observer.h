//
// Created by jmartens on 02.07.2023.
//

#ifndef GALAXIS_BLE_OBSERVER_H
#define GALAXIS_BLE_OBSERVER_H

#include <cstdint>
#include "galaxis-message.h"
#include "view-update-message.h"

class Observer {
public:
    virtual ~Observer()= default;
    virtual void update(ViewUpdateMessage param) = 0;
};


#endif //GALAXIS_BLE_OBSERVER_H
