//
// Created by jmartens on 04.11.2023.
//

#include "main_menu_view.h"

#include <utility>
#include "core/lv_disp.h"
#include "ui.h"
#include "settings.h"
#include "view-update-message.h"

MainMenuView::MainMenuView(RotaryEncoder *encoder, std::shared_ptr<MainMenuController> controller,
                           std::shared_ptr<MainMenuModel> model) : _encoder(encoder),
                                                                   _controller(std::move(controller)),
                                                                   _model(std::move(model)) {
    _model->registerObserver(this);
}

void MainMenuView::show() {
    updateMenuItem();
    lv_scr_load_anim(ui_MainMenu, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

Screen MainMenuView::loop() {
    int position = _encoder->getPosition();
    if (_lastPosition != position) {
        _controller->move(position);
        _lastPosition = position;
    }

    int button = digitalRead(PIN_ENC_BUTTON);
    if (button != lastButtonState && ((millis() - lastButtonPress) > debounceTimeSpan)) {
        if (button == HIGH) {
            _controller->btnClick(position);
        }
        lastButtonState = button;
        lastButtonPress = millis();
    }

    return _model->getSelectedMenuItem();
}

void MainMenuView::update(int param) {
    switch ((ViewUpdateMessage) param) {
        case Coordinates:
        case SearchResult:
        case ShipCount:
        case Active:
        case Hint:
        case Connected:
        case GameOver:
            break;
        case MenuItemChanged:
            updateMenuItem();
            break;
    }
}

void MainMenuView::updateMenuItem() {
    String txt = "";
    if (_model->getMenu() == 0)
        txt = MAIN_MENU_JOIN;
    if (_model->getMenu() == 1)
        txt = MAIN_MENU_NEW_GAME;
    if (_model->getMenu() == 2)
        txt = MAIN_MENU_SINGLE;

    lv_label_set_text(ui_MainMenuItem, txt.c_str());
}
