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

class BLECentralGame : public AbstractGame {
public:
    BLECentralGame();

    static BLECentralGame *getInstance();

    ~BLECentralGame() override;

private:
    static BLECentralGame *_instance;
    static std::vector<BLEDevice> devices;
    std::unique_ptr<Galaxis> _galaxis;
    static uint8_t _connectionCount;
    static bool _isScanning;
    static bool _gameStarted;

    static void discoverHandler(BLEDevice bleDevice);

    static void galaxisCharacteristicWritten(BLEDevice bleDevice, BLECharacteristic characteristic);

    void makeGuess(uint8_t playerId, uint8_t x, uint8_t y) override;

    static void peripheralDisconnectHandler(BLEDevice bleDevice);

    void SendGameOverNotification(uint8_t winner) const;

    void SendNextPlayerNotification() const;

    void SendGuessResponse(uint8_t receiver, uint8_t guessResult, uint8_t discovered) const;

    void NotifyUiConnected(bool connected);

    void NotifyUiClientConnected();

    static void SendPairingMessage();

    static void stopScanning();

    static void startScanning();

    static void logMessage(const GalaxisMessage &galaxisMessage);

    void startGame() override;
};


#endif //GALAXIS_BLE_CENTRAL_GAME_H
