//
// Created by jmartens on 04.11.2023.
//

#include "main_menu_model.h"
#include "view-update-message.h"

uint8_t MainMenuModel::getMenu() const {
    return _menu;
}

void MainMenuModel::setMenu(uint8_t menu) {
    if (_menu == menu)
        return;

    _menu = menu;
    notifyView(ViewUpdateMessage::MenuItemChanged);
}

Screen MainMenuModel::getSelectedMenuItem() const {
    return _selectedMenuItem;
}

void MainMenuModel::setSelectedMenuItem(Screen selectedMenuItem) {
    _selectedMenuItem = selectedMenuItem;
}
