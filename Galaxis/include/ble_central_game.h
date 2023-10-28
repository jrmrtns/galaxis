//
// Created by jmartens on 25.10.2023.
//

#ifndef GALAXIS_BLE_CENTRAL_GAME_H
#define GALAXIS_BLE_CENTRAL_GAME_H


#include "subject.h"
#include "abstract-game.h"
#include "BLEDevice.h"

class BLECentralGame : public Subject, public AbstractGame {
public:
    BLECentralGame();

    static BLECentralGame *getInstance();

private:
    static BLECentralGame *_instance;
    static BLECharacteristic _galaxisCharacteristic;

    static void discoverHandler(BLEDevice peripheral);

    static void galaxisCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic);

    void makeGuess(uint8_t playerId, uint8_t x, uint8_t y) override;

    static void peripheralDisconnectHandler(BLEDevice central);
};


#endif //GALAXIS_BLE_CENTRAL_GAME_H
