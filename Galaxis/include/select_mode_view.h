#ifndef GALAXIS_SELECT_MODE_VIEW_H
#define GALAXIS_SELECT_MODE_VIEW_H

#include "view.h"
#include "RotaryEncoder.h"
#include "abstract-game.h"
#include "screen.h"
#include <memory>

class SelectModeView : public IView {
public:
    SelectModeView(RotaryEncoder *encoder);
    void show() override;
    Screen loop() override;

private:
    RotaryEncoder *_encoder;
    int _lastPosition = 0;
    int _lastButtonState = HIGH;
    uint32_t _lastButtonPress = 0;
    uint8_t _selectedMode = 0;
    bool _confirmed = false;
    
    void updateUi();
};

#endif //GALAXIS_SELECT_MODE_VIEW_H
