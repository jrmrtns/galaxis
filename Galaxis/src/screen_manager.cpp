//
// Created by jmartens on 18.10.2023.
//

#include "screen_manager.h"
#include "galaxis_game_view.h"
#include "ble_device_game.h"
#include "ble_central_game.h"
#include "single_player_game.h"
#include "main_menu_controller.h"
#include "main_menu_model.h"
#include "main_menu_view.h"
#include "screen.h"
#include "settings.h"

ScreenManager::ScreenManager(RotaryEncoder *encoder) : _encoder(encoder) {}

void ScreenManager::loop() {
    _encoder->tick();
    int tick = _encoder->getPosition();
    if (tick != _lastPosition){
        _lastPosition = tick;
    }

    int result = 0;
    if (_view != nullptr)
        result = _view->loop();

    if (result != 0) {
        _view = nullptr;
        _encoder->setPosition((1000 * MAX_X * MAX_Y));
        BLE.end();

        BLE.begin();
        show((Screen) result);
    }
}

void ScreenManager::show(Screen screen) {
    switch (screen) {
        case NONE:
            break;
        case MENU:
            showMainMenu();
            break;
        case SINGLE_GAME:
            showSingleGameView();
            break;
        case CENTRAL_GAME:
            showCentralGameView();
            break;
        case PERIPHERAL_GAME:
            showPeriheralGameView();
            break;
        case GAME_OVER_SCREEN:
            break;
    }
}

void ScreenManager::showSingleGameView() {
    auto gameModel = std::make_shared<GalaxisGameModel>();
    randomSeed(1);
    //randomSeed(micros());

    std::shared_ptr<AbstractGame> game = std::make_shared<SinglePlayerGame>();

    auto gameController = std::make_shared<GalaxisGameController>(game, gameModel);
    _view = std::make_shared<GalaxisGameView>(_encoder, gameController, gameModel);
    _view->show();
}

void ScreenManager::showMainMenu() {
    auto model = std::make_shared<MainMenuModel>();
    auto controller = std::make_shared<MainMenuController>(model);
    _view = std::make_shared<MainMenuView>(_encoder, controller, model);
    _view->show();
}

void ScreenManager::showCentralGameView() {
    auto gameModel = std::make_shared<GalaxisGameModel>();
    randomSeed(1);
    //randomSeed(micros());

    std::shared_ptr<AbstractGame> game = std::make_shared<BLECentralGame>();
    gameModel->setMe(0);

    auto gameController = std::make_shared<GalaxisGameController>(game, gameModel);
    _view = std::make_shared<GalaxisGameView>(_encoder, gameController, gameModel);
    _view->show();
}

void ScreenManager::showPeriheralGameView() {
    auto gameModel = std::make_shared<GalaxisGameModel>();

    std::shared_ptr<AbstractGame> game = std::make_shared<BLEDeviceGame>();
    gameModel->setMe(1);

    auto gameController = std::make_shared<GalaxisGameController>(game, gameModel);
    _view = std::make_shared<GalaxisGameView>(_encoder, gameController, gameModel);
    _view->show();
}
