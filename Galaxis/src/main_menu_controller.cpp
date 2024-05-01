//
// Created by jmartens on 04.11.2023.
//

#include "main_menu_controller.h"
#include <utility>

#define MENU_ITEM_COUNT 3

MainMenuController::MainMenuController(std::shared_ptr<MainMenuModel> model) : _model(std::move(model)) {}

void MainMenuController::move(int position) {
    uint32_t p = position % (MENU_ITEM_COUNT);
    _model->setMenu(p);
}

void MainMenuController::btnClick(int position) {
    uint32_t p = position % (MENU_ITEM_COUNT);
    switch (p) {
        case 0:
            _model->setSelectedMenuItem(Screen::PERIPHERAL_GAME);
            break;

        case 1:
            _model->setSelectedMenuItem(Screen::CENTRAL_GAME);
            break;

        case 2:
            _model->setSelectedMenuItem(Screen::SINGLE_GAME);
            break;

        default:
            break;
    }
}
