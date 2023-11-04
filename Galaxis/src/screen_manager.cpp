//
// Created by jmartens on 18.10.2023.
//

#include "screen_manager.h"

ScreenManager::ScreenManager(RotaryEncoder *encoder) : _encoder(encoder) {}

void ScreenManager::loop() {
    int tick = _encoder->getPosition();
    if (tick != _lastPosition){
        _lastPosition = tick;
    }
}
