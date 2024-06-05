//
// Created by jmartens on 04.11.2023.
//

#ifndef GALAXIS_MAIN_MENU_VIEW_H
#define GALAXIS_MAIN_MENU_VIEW_H


#include "observer.h"
#include "view.h"
#include "memory"
#include "RotaryEncoder.h"
#include "main_menu_model.h"
#include "main_menu_controller.h"

class MainMenuView: public Observer, public IView  {
public:
    MainMenuView(RotaryEncoder *encoder, std::shared_ptr<MainMenuController> controller, std::shared_ptr<MainMenuModel> model);

    void show() override ;

    Screen loop() override;

    void update(ViewUpdateMessage param) override;
private:
    RotaryEncoder *_encoder;
    std::shared_ptr<MainMenuController> _controller;
    std::shared_ptr<MainMenuModel> _model;
    int _lastPosition = 0;
    int _lastButtonState = HIGH;
    uint32_t _lastButtonPress = 0;
    uint32_t _debounceTimeSpan = 25;

    void updateMenuItem();
};


#endif //GALAXIS_MAIN_MENU_VIEW_H
