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
#include "game_over_view.h"
#include "ui.h"

ScreenManager::ScreenManager(RotaryEncoder *encoder) : _encoder(encoder) {}

void ScreenManager::loop() {
    _encoder->tick();
    int tick = _encoder->getPosition();
    if (tick != _lastPosition){
        _lastPosition = tick;
    }

    Screen result = Screen::NO_CHANGE;
    if (_currentView != nullptr)
        result = _currentView->loop();

    if (result != Screen::NO_CHANGE) {
        _currentView = nullptr;
        _encoder->setPosition((1000 * MAX_X * MAX_Y));
        BLE.end();

        BLE.begin();
        show(result);
    }
}

void ScreenManager::show(Screen screen) {
    switch (screen) {
        case NO_CHANGE:
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
            showGameOverView();
            break;
        case WINNER_SCREEN:
            showWinnerView();
            break;
    }
}

void ScreenManager::showSingleGameView() {
    auto gameModel = std::make_shared<GalaxisGameModel>();
    gameModel->setConnected(true);
    gameModel->setStarted(true);
#ifdef RND
    randomSeed(1);
#else
    randomSeed(micros());
#endif

    std::shared_ptr<AbstractGame> game = std::make_shared<SinglePlayerGame>();

    auto gameController = std::make_shared<GalaxisGameController>(game, gameModel);
    _currentView = std::make_shared<GalaxisGameView>(_encoder, gameController, gameModel);
    _currentView->show();
}

void ScreenManager::showMainMenu() {
    auto model = std::make_shared<MainMenuModel>();
    auto controller = std::make_shared<MainMenuController>(model);
    _currentView = std::make_shared<MainMenuView>(_encoder, controller, model);
    _currentView->show();
}

void ScreenManager::showCentralGameView() {
    auto gameModel = std::make_shared<GalaxisGameModel>();
#ifdef RND
    randomSeed(1);
#else
    randomSeed(micros());
#endif

    std::shared_ptr<AbstractGame> game = std::make_shared<BLECentralGame>();
    gameModel->setMe(0);

    auto gameController = std::make_shared<GalaxisGameController>(game, gameModel);
    _currentView = std::make_shared<GalaxisGameView>(_encoder, gameController, gameModel);
    _currentView->show();
}

void ScreenManager::showPeriheralGameView() {
    auto gameModel = std::make_shared<GalaxisGameModel>();

    std::shared_ptr<AbstractGame> game = std::make_shared<BLEDeviceGame>();

    auto gameController = std::make_shared<GalaxisGameController>(game, gameModel);
    _currentView = std::make_shared<GalaxisGameView>(_encoder, gameController, gameModel);
    _currentView->show();
}

void ScreenManager::showGameOverView() {
    lv_label_set_text(ui_GameOverItem, String(GAME_OVER_MESSAGE).c_str());
    lv_label_set_text(ui_GameOverHint, String(GAME_OVER_HINT).c_str());
    _currentView = std::make_shared<GameOverView>(_encoder);
    _currentView->show();
}

void ScreenManager::showWinnerView() {
    lv_label_set_text(ui_GameOverItem, String(GAME_OVER_WINNER_MESSAGE).c_str());
    lv_label_set_text(ui_GameOverHint, String(GAME_OVER_WINNER_HINT).c_str());
    _currentView = std::make_shared<GameOverView>(_encoder);
    _currentView->show();
}
