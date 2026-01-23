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

    // Gibt die Koordinaten des angegebenen Schiffes zurück (shipIndex 0-3)
    void getShipCoordinates(uint8_t shipIndex, uint8_t& x, uint8_t& y) const;

private:
    RotaryEncoder* _encoder;
    int _lastPosition = 0;
    int _lastButtonState = HIGH;
    uint32_t _lastButtonPress = 0;
    uint32_t _debounceTimeSpan = 50;
    uint8_t _focusedElement = 0;  // 0-3: Schiffe, 4: OK-Button
    bool _editMode = false;  // false = Navigation zwischen Elementen, true = Koordinaten ändern

    // Koordinaten für die 4 Schiffe als lineare Positionen (0 bis MAX_X*MAX_Y-1)
    uint16_t _shipPositions[4] = {0, 1, 2, 3};

    void updateShipLabel(uint8_t shipIndex);
    void updateFocus();
    bool areCoordinatesUnique();
    void updateShipPosition(int encoderValue);
    void positionToCoords(uint16_t position, uint8_t& x, uint8_t& y) const;
    bool isPositionUsedByOtherShip(uint8_t currentShipIndex, uint16_t position) const;
};


#endif //GALAXIS_HIDE_SHIPS_VIEW_H
