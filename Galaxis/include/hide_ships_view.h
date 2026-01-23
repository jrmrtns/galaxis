#ifndef GALAXIS_HIDE_SHIPS_VIEW_H
#define GALAXIS_HIDE_SHIPS_VIEW_H
#include "view.h"
#include "RotaryEncoder.h"

class HideShipsView : public IView
{
public:
    explicit HideShipsView(RotaryEncoder* encoder);
    Screen loop() override;
    void show() override;

private:
    RotaryEncoder* _encoder;
    int _lastPosition = 0;
    uint8_t _focusedElement = 0;
    void setFocus(int position);
};


#endif //GALAXIS_HIDE_SHIPS_VIEW_H
