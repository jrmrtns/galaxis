//
// Created by jmartens on 18.10.2023.
//

#ifndef GALAXIS_SCREEN_MANAGER_H
#define GALAXIS_SCREEN_MANAGER_H


#include "RotaryEncoder.h"

class ScreenManager {
private :
    RotaryEncoder *_encoder;
    int _lastPosition = 0;
public:
    explicit ScreenManager(RotaryEncoder *encoder);

    void tick();
};


#endif //GALAXIS_SCREEN_MANAGER_H
