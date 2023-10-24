//
// Created by jmartens on 17.10.2023.
//

#ifndef GALAXIS_BLE_CENTRAL_GAME_H
#define GALAXIS_BLE_CENTRAL_GAME_H

#include "subject.h"
#include "abstract-game.h"
#include "galaxis.h"
#include <ArduinoBLE.h>
#include <memory>

class BLECentralGame: public Subject, public AbstractGame {
public:
    BLECentralGame();

public:
    static BLECentralGame *getInstance();

private:
    static BLECentralGame *_instance;
    static void blePeripheralConnectHandler(BLEDevice central);
    static void blePeripheralDisconnectHandler(BLEDevice central);
    static void galaxisCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic);

    std::unique_ptr<Galaxis> _galaxis;
    void makeGuess(uint8_t playerId, uint8_t x, uint8_t y) override;

    void SendGameOverNotification(uint8_t winner) const;

    void SendNextPlayerNotification(uint8_t nextPlayer) const;

    void SendGuessResponse(uint8_t receiver, uint8_t guessResult, uint8_t discovered) const;
};

#endif //GALAXIS_BLE_CENTRAL_GAME_H
