//
// Created by jmartens on 05.11.2023.
//

#ifndef GALAXIS_GAME_OVER_VIEW_H
#define GALAXIS_GAME_OVER_VIEW_H

#include "view.h"
#include "RotaryEncoder.h"

class GameOverView : public IView {
public:
    explicit GameOverView(RotaryEncoder *encoder);

    Screen loop() override;

    void show() override;
private:
    RotaryEncoder *_encoder;
    int _lastPosition = 0;
    int _lastButtonState = HIGH;
    uint32_t _lastButtonPress = 0;
    uint32_t _debounceTimeSpan = 25;
};


#endif //GALAXIS_GAME_OVER_VIEW_H
