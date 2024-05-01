//
// Created by jmartens on 04.11.2023.
//

#ifndef GALAXIS_MAIN_MENU_MODEL_H
#define GALAXIS_MAIN_MENU_MODEL_H


#include "subject.h"
#include "screen.h"

class MainMenuModel : public Subject {
private:
    uint8_t _menu = 0;
    Screen _selectedMenuItem = Screen::NO_CHANGE;
public:
    Screen getSelectedMenuItem() const;

    void setSelectedMenuItem(Screen selectedMenuItem);

    uint8_t getMenu() const;

    void setMenu(uint8_t menu);
};


#endif //GALAXIS_MAIN_MENU_MODEL_H
