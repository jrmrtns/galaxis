//
// Created by jmartens on 04.11.2023.
//

#include "main_menu_controller.h"
#include <utility>

MainMenuController::MainMenuController(std::shared_ptr<MainMenuModel> model) : _model(std::move(model)) { }

void MainMenuController::move(int position) {
    uint32_t p = position % (3);
    _model->setMenu(p);
}

void MainMenuController::btnClick(int position) {
    uint32_t p = position % (3);
    if (p == 0)
        _model->setSelectedMenuItem(Screen::PERIPHERAL_GAME);
    if (p == 1)
        _model->setSelectedMenuItem(Screen::CENTRAL_GAME);
    if (p == 2)
        _model->setSelectedMenuItem(Screen::SINGLE_GAME);
}
