//
// Created by jmartens on 18.10.2023.
//

#ifndef GALAXIS_SCREEN_MANAGER_H
#define GALAXIS_SCREEN_MANAGER_H


#include "RotaryEncoder.h"

class ScreenManager {
public:
    explicit ScreenManager(RotaryEncoder *encoder);

    void tick();

private :
    RotaryEncoder *_encoder;
    int _lastPosition = 0;
};


#endif //GALAXIS_SCREEN_MANAGER_H
