//
// Created by jmartens on 05.11.2023.
//

#ifndef GALAXIS_SETTINGS_VIEW_H
#define GALAXIS_SETTINGS_VIEW_H

#include "view.h"
#include "RotaryEncoder.h"

class SettingsView : public IView {
public:
    explicit SettingsView(RotaryEncoder *encoder);

    Screen loop() override;

    void show() override;
private:
    RotaryEncoder *_encoder;
    int _lastPosition = 0;
    int _lastButtonState = HIGH;
    uint32_t _lastButtonPress = 0;
    uint32_t _debounceTimeSpan = 50;
    uint8_t _focusedElement = 0;
    void setFocus(int position);
    bool click();

    void updateStates() const;
};


#endif //GALAXIS_SETINGS_VIEW_H
