//
// Created by jmartens on 17.10.2023.
//

#ifndef GALAXIS_GALAXIS_GAME_VIEW_H
#define GALAXIS_GALAXIS_GAME_VIEW_H


#include "observer.h"
#include "galaxis_game_model.h"
#include "RotaryEncoder.h"
#include "galaxis_game_controller.h"
#include "view.h"

class GalaxisGameView : public Observer, public IView {
public:
    GalaxisGameView(RotaryEncoder *encoder, std::shared_ptr<GalaxisGameController> galaxisController, std::shared_ptr<GalaxisGameModel> galaxisModel);

    ~GalaxisGameView() override;

    void show() override;

    Screen loop() override;

    void update(ViewUpdateMessage param) override;

private:
    RotaryEncoder *_encoder;
    std::shared_ptr<GalaxisGameController> _galaxisController;
    std::shared_ptr<GalaxisGameModel> _galaxisModel;

    void updateCoordinates();
    void updateSearchResult();

    int _lastPosition = 0;
    int _lastButtonState = HIGH;
    uint32_t _lastButtonPress = 0;
    uint32_t _debounceTimeSpan = 25;
    uint32_t _endAnimationTime = 0;
    uint32_t _nextIdleToneTime = 0;
    uint32_t _startTime = 0;
    String _elapsedTime = "";

    void updateActive();

    void updateHint();

    void updateConnected();

    void updateGameOver();

    void updateShipCount();

    void updateRound();

    void startSearching();

    void endSearching();

    void playIdle();

    void playFeedback(uint8_t searchResult) const;

    void showShipCount(uint8_t i) const;

    uint8_t getIndicatorIndex() const;

    void resetNextIdleTime();

    void drawElapsedTime();

    void startGame();
};


#endif //GALAXIS_GALAXIS_GAME_VIEW_H
