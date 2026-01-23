#include "hide_ships_view.h"

#include "RotaryEncoder.h"
#include "core/lv_disp.h"
#include "screens/ui_HideShips.h"
#include "widgets/lv_label.h"
#include "settings.h"
#include <cstdio>

HideShipsView::HideShipsView(RotaryEncoder* encoder) : IView(), _encoder(encoder)
{
}

void HideShipsView::positionToCoords(uint16_t position, uint8_t& x, uint8_t& y) const
{
    // Gleiche Logik wie im galaxis_game_controller
    uint32_t p = position % (MAX_X * MAX_Y);
    x = p / MAX_Y;
    y = p % MAX_Y;
}

void HideShipsView::getShipCoordinates(uint8_t shipIndex, uint8_t& x, uint8_t& y) const
{
    if (shipIndex < 4)
    {
        positionToCoords(_shipPositions[shipIndex], x, y);
    }
}

bool HideShipsView::isPositionUsedByOtherShip(uint8_t currentShipIndex, uint16_t position) const
{
    uint8_t x1, y1;
    positionToCoords(position, x1, y1);

    for (uint8_t i = 0; i < 4; i++)
    {
        if (i != currentShipIndex)
        {
            uint8_t x2, y2;
            positionToCoords(_shipPositions[i], x2, y2);

            if (x1 == x2 && y1 == y2)
            {
                return true;
            }
        }
    }
    return false;
}

void HideShipsView::updateShipLabel(uint8_t shipIndex)
{
    char label[4];
    uint8_t x, y;
    positionToCoords(_shipPositions[shipIndex], x, y);

    // Formatierung: A1 bis I7 (A-I sind X-Koordinaten 0-8, 1-7 sind Y-Koordinaten 0-6)
    snprintf(label, sizeof(label), "%c%d", 'A' + x, y + 1);

    lv_obj_t* shipLabel = nullptr;

    switch(shipIndex)
    {
        case 0:
            shipLabel = ui_Ship1;
            lv_label_set_text(ui_Ship1, label);
            break;
        case 1:
            shipLabel = ui_Ship2;
            lv_label_set_text(ui_Ship2, label);
            break;
        case 2:
            shipLabel = ui_Ship3;
            lv_label_set_text(ui_Ship3, label);
            break;
        case 3:
            shipLabel = ui_Ship4;
            lv_label_set_text(ui_Ship4, label);
            break;
    }

    // Prüfe ob diese Koordinate bereits von einem anderen Schiff verwendet wird
    if (shipLabel != nullptr)
    {
        bool isDuplicate = isPositionUsedByOtherShip(shipIndex, _shipPositions[shipIndex]);

        if (isDuplicate && shipIndex == _focusedElement && _editMode)
        {
            // Setze USER_1 State für Duplikat und definiere rote Farbe dafür
            lv_obj_add_state(shipLabel, LV_STATE_USER_1);
            lv_obj_set_style_text_color(shipLabel, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_USER_1);
        }
        else
        {
            // Entferne USER_1 State
            lv_obj_clear_state(shipLabel, LV_STATE_USER_1);
        }
    }
}

void HideShipsView::updateFocus()
{
    // Aktualisiere den Fokus-Status aller Elemente
    lv_obj_t* ships[4] = {ui_Ship1, ui_Ship2, ui_Ship3, ui_Ship4};

    for (uint8_t i = 0; i < 4; i++)
    {
        if (i == _focusedElement)
        {
            lv_obj_add_state(ships[i], LV_STATE_FOCUSED);
            if (_editMode)
            {
                lv_obj_add_state(ships[i], LV_STATE_EDITED);
            }
            else
            {
                lv_obj_clear_state(ships[i], LV_STATE_EDITED);
            }
        }
        else
        {
            lv_obj_clear_state(ships[i], LV_STATE_FOCUSED);
            lv_obj_clear_state(ships[i], LV_STATE_EDITED);
        }
    }

    // OK-Button Fokus
    if (_focusedElement == 4)
    {
        lv_obj_add_state(ui_okButton1, LV_STATE_FOCUSED);
    }
    else
    {
        lv_obj_clear_state(ui_okButton1, LV_STATE_FOCUSED);
    }
}

bool HideShipsView::areCoordinatesUnique()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            uint8_t x1, y1, x2, y2;
            positionToCoords(_shipPositions[i], x1, y1);
            positionToCoords(_shipPositions[j], x2, y2);

            if (x1 == x2 && y1 == y2)
            {
                return false;
            }
        }
    }
    return true;
}

void HideShipsView::updateShipPosition(int encoderValue)
{
    // Konvertiere zu positivem Modulo-Wert für endloses Durchlaufen
    int maxPos = MAX_X * MAX_Y;
    int pos = encoderValue % maxPos;
    if (pos < 0) pos += maxPos;

    _shipPositions[_focusedElement] = pos;
    updateShipLabel(_focusedElement);
}

Screen HideShipsView::loop()
{
    int position = _encoder->getPosition();

    if (_lastPosition != position)
    {
        _lastPosition = position;

        if (_editMode)
        {
            // Im Edit-Modus: Koordinaten des aktuellen Schiffs ändern
            updateShipPosition(position);
        }
        else
        {
            // Im Navigations-Modus: Zwischen Schiffen und OK-Button wechseln
            int numElements = 5; // 4 Schiffe + 1 OK-Button
            int newFocus = position % numElements;
            if (newFocus < 0) newFocus += numElements;

            _focusedElement = newFocus;
            updateFocus();
        }
    }

    // Button-Handling
    int button = digitalRead(PIN_ENC_BUTTON);
    if (button != _lastButtonState && ((millis() - _lastButtonPress) > _debounceTimeSpan))
    {
        if (button == HIGH)
        {
            // Button wurde losgelassen
            if (_editMode)
            {
                // Edit-Modus beenden → zurück zur Navigation
                _editMode = false;

                // Setze Encoder auf aktuelles fokussiertes Element
                _encoder->setPosition(_focusedElement);
                _lastPosition = _focusedElement;

                // Aktualisiere alle Labels um Farben zurückzusetzen
                for (uint8_t i = 0; i < 4; i++)
                {
                    updateShipLabel(i);
                }

                updateFocus();
            }
            else
            {
                // Navigations-Modus
                if (_focusedElement < 4)
                {
                    // Schiff wurde ausgewählt → Edit-Modus aktivieren
                    _editMode = true;

                    // Setze Encoder auf aktuelle Position des Schiffs
                    _encoder->setPosition(_shipPositions[_focusedElement]);
                    _lastPosition = _shipPositions[_focusedElement];

                    updateFocus();
                }
                else if (_focusedElement == 4)
                {
                    // OK-Button wurde gedrückt
                    if (areCoordinatesUnique())
                    {
                        // Koordinaten sind gültig, weiter zum Spiel
                        return Screen::PERIPHERAL_GAME;
                    }
                    else
                    {
                        // Koordinaten nicht eindeutig, fokussiere erstes Schiff
                        _focusedElement = 0;
                        _encoder->setPosition(0);
                        _lastPosition = 0;
                        updateFocus();
                    }
                }
            }
        }
        _lastButtonState = button;
        _lastButtonPress = millis();
    }

    return Screen::NO_CHANGE;
}

void HideShipsView::show()
{
    // Initialisiere Labels mit aktuellen Koordinaten
    for (uint8_t i = 0; i < 4; i++)
    {
        updateShipLabel(i);
    }

    // Starte im Navigations-Modus mit Fokus auf erstem Schiff
    _editMode = false;
    _focusedElement = 0;
    _encoder->setPosition(0);
    _lastPosition = 0;

    updateFocus();

    lv_scr_load_anim(ui_HideShips, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}
