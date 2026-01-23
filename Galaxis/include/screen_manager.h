//
// Created by jmartens on 18.10.2023.
//

#ifndef GALAXIS_SCREEN_MANAGER_H
#define GALAXIS_SCREEN_MANAGER_H

#include "RotaryEncoder.h"
#include "galaxis_game_view.h"
#include "screen.h"

class ScreenManager {
public:
    explicit ScreenManager(RotaryEncoder *encoder);

    void loop();

    void show(Screen screen);

    static uint8_t getSelectedGameMode();
    static void setSelectedGameMode(uint8_t mode);

private :
    RotaryEncoder *_encoder;

    int _lastPosition = 0;

    std::shared_ptr<IView> _currentView;

    void showMainMenu();

    void showCentralGameView();

    void showPeriheralGameView();

    void showGameOverView();

    void showWinnerView();

    void showSettingsView();

    void showSelectModeView();

    static uint8_t _selectedGameMode;
};

#endif //GALAXIS_SCREEN_MANAGER_H
