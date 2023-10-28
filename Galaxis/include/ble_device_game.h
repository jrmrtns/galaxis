//
// Created by jmartens on 17.10.2023.
//

#ifndef GALAXIS_BLE_DEVICE_GAME_H
#define GALAXIS_BLE_DEVICE_GAME_H

#include "subject.h"
#include "abstract-game.h"
#include "galaxis.h"
#include <ArduinoBLE.h>
#include <memory>

class BLEDeviceGame : public Subject, public AbstractGame {
public:
    BLEDeviceGame();

    static BLEDeviceGame *getInstance();

private:
    static BLEDeviceGame *_instance;

    static void peripheralConnectHandler(BLEDevice central);

    static void peripheralDisconnectHandler(BLEDevice central);

    static void galaxisCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic);

    static void galaxisCharacteristicSubscribed(BLEDevice central, BLECharacteristic characteristic);

    std::unique_ptr<Galaxis> _galaxis;

    void makeGuess(uint8_t playerId, uint8_t x, uint8_t y) override;

    void SendGameOverNotification(uint8_t winner) const;

    void SendNextPlayerNotification() const;

    void SendGuessResponse(uint8_t receiver, uint8_t guessResult, uint8_t discovered) const;
};

#endif //GALAXIS_BLE_DEVICE_GAME_H
