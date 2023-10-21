//
// Created by jmartens on 17.10.2023.
//

#ifndef GALAXIS_GALAXIS_GAME_VIEW_H
#define GALAXIS_GALAXIS_GAME_VIEW_H


#include "observer.h"
#include "galaxis_game_model.h"
#include "RotaryEncoder.h"
#include "galaxis_game_controller.h"

class GalaxisGameView : public Observer {
public:
    GalaxisGameView(RotaryEncoder *encoder, GalaxisGameController *galaxisController, std::shared_ptr<GalaxisGameModel> galaxisModel);

    ~GalaxisGameView() override;

    void show();

    void tick();

    void update(int param) override;

private:
    std::shared_ptr<GalaxisGameModel> _galaxisModel;
    GalaxisGameController *_galaxisController;

    void updateCoordinates();
    void updateSearchResult();

    RotaryEncoder *_encoder;
    int _lastPosition = 0;
    int lastButtonState = HIGH;
    uint32_t lastButtonPress = 0;
    uint32_t debounceTimeSpan = 25;

    void updateShipCount();

    void updateActive();
};


#endif //GALAXIS_GALAXIS_GAME_VIEW_H
