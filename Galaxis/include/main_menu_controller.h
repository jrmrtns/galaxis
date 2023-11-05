//
// Created by jmartens on 04.11.2023.
//

#ifndef GALAXIS_MAIN_MENU_CONTROLLER_H
#define GALAXIS_MAIN_MENU_CONTROLLER_H

#include "message_observer.h"
#include "memory"
#include "main_menu_model.h"

class MainMenuController {
public:
    explicit MainMenuController(std::shared_ptr<MainMenuModel> model);

    void move(int position);

    void btnClick(int position);

private:
    std::shared_ptr<MainMenuModel> _model;
};


#endif //GALAXIS_MAIN_MENU_CONTROLLER_H
