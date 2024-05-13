//
// Created by jmartens on 25.10.2023.
//

#ifndef GALAXIS_BLE_CENTRAL_GAME_H
#define GALAXIS_BLE_CENTRAL_GAME_H


#include "subject.h"
#include "abstract-game.h"
#include "BLEDevice.h"
#include "galaxis.h"
#include "settings.h"

class BLECentralGame : public Subject, public AbstractGame {
public:
    BLECentralGame();

    static BLECentralGame *getInstance();

    ~BLECentralGame() override;

    void shutdown() override;

private:
    static BLECentralGame *_instance;
    static BLECharacteristic _galaxisCharacteristic[MAX_PERIPHERALS];
    std::unique_ptr<Galaxis> _galaxis;
    static uint8_t _connectionCount;
    static bool _isScanning;

    static void discoverHandler(BLEDevice peripheral);

    static void galaxisCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic);

    void makeGuess(uint8_t playerId, uint8_t x, uint8_t y) override;

    static void peripheralDisconnectHandler(BLEDevice central);

    void SendGameOverNotification(uint8_t winner) const;

    void SendNextPlayerNotification() const;

    void SendGuessResponse(uint8_t receiver, uint8_t guessResult, uint8_t discovered) const;

    void NotifyUiConnected(bool connected);

    static void SendPairingMessage();

    void stopScanning();

    static void startScanning();
};


#endif //GALAXIS_BLE_CENTRAL_GAME_H
