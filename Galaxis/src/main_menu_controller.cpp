//
// Created by jmartens on 04.11.2023.
//

#include "main_menu_controller.h"
#include <utility>

#define MENU_ITEM_COUNT 3

MainMenuController::MainMenuController(std::shared_ptr<MainMenuModel> model) : _model(std::move(model)) { }

void MainMenuController::move(int position) {
    uint32_t p = position % (MENU_ITEM_COUNT);
    _model->setMenu(p);
}

void MainMenuController::btnClick(int position) {
    uint32_t p = position % (MENU_ITEM_COUNT);
    if (p == 0)
        _model->setSelectedMenuItem(Screen::PERIPHERAL_GAME);
    if (p == 1)
        _model->setSelectedMenuItem(Screen::CENTRAL_GAME);
    if (p == 2)
        _model->setSelectedMenuItem(Screen::SINGLE_GAME);
    if (p == 3){
        //ESP.deepSleep(30 * 1000000);
        //esp_sleep_enable_timer_wakeup(30 * 1000000);
        //esp_deep_sleep_start();
    }
}
