//
// Created by jmartens on 25.10.2023.
//

#include "ble_central_game.h"
#include "settings.h"
#include <ArduinoBLE.h>

#include <memory>

BLECentralGame *BLECentralGame::_instance = nullptr;
BLECharacteristic BLECentralGame::_galaxisCharacteristic[MAX_PERIPHERALS];
uint8_t BLECentralGame::_connectionCount = 0;
bool BLECentralGame::_isScanning = false;

BLECentralGame::BLECentralGame() {
    _instance = this;

    _galaxis = std::make_unique<Galaxis>(single_board, false);
    _galaxis->dumpCurrent();

    BLE.setEventHandler(BLEDiscovered, discoverHandler);
    BLE.setEventHandler(BLEDisconnected, peripheralDisconnectHandler);
    startScanning();
}

BLECentralGame::~BLECentralGame() {
    _instance = nullptr;
}

void BLECentralGame::shutdown() {
    BLE.disconnect();
    BLE.stopScan();
    removeAllObservers();
}

BLECentralGame *BLECentralGame::getInstance() {
    return _instance;
}

void BLECentralGame::discoverHandler(BLEDevice peripheral) {
    if (!peripheral.connect()) {
        return;
    }

    if (!peripheral.discoverAttributes()) {
        peripheral.disconnect();
        return;
    }

    BLECharacteristic characteristic = peripheral.characteristic(GALAXIS_CHARACTERISTIC_UUID);
    characteristic.setEventHandler(BLEWritten, galaxisCharacteristicWritten);
    if (!characteristic || !characteristic.canSubscribe()) {
        peripheral.disconnect();
        return;
    }

    _galaxisCharacteristic[_connectionCount] = characteristic;
    characteristic.subscribe();

    SendPairingMessage();

    startScanning();
}

void BLECentralGame::SendPairingMessage() {
    uint16_t id = getInstance()->_galaxis->join();
    GalaxisMessage message = {0};
    message.msgType = PAIRING_RESPONSE;
    message.command = CONNECT;
    message.id = 0;
    message.param1 = true;
    message.param2 = id;
    _galaxisCharacteristic[_connectionCount].writeValue(&message, sizeof(GalaxisMessage), true);
    _connectionCount++;
    getInstance()->NotifyUiConnected(true);
}

// NOLINTNEXTLINE
void BLECentralGame::peripheralDisconnectHandler(BLEDevice central) {
    Serial.print("Disconnected event: ");
    Serial.println(central.address());
    startScanning();
    BLECentralGame::getInstance()->NotifyUiConnected(false);
}

// NOLINTNEXTLINE
void BLECentralGame::galaxisCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
    GalaxisMessage galaxisMessage = {0};
    characteristic.readValue(&galaxisMessage, sizeof(galaxisMessage));

    printf("Type %d \n\n", galaxisMessage.msgType);

    Serial.print(galaxisMessage.msgType);
    Serial.print(":");
    Serial.print(galaxisMessage.command);
    Serial.print(":");
    Serial.print(galaxisMessage.id);
    Serial.print(":");

    Serial.print(galaxisMessage.param1);
    Serial.print(":");
    Serial.println(galaxisMessage.param2);

    if (galaxisMessage.msgType != REQUEST)
        return;

    if (galaxisMessage.command == SEARCH) {
        BLECentralGame::getInstance()->makeGuess(galaxisMessage.id, galaxisMessage.param1, galaxisMessage.param2);
    }

    if (galaxisMessage.command == NEXT) {
        BLECentralGame::getInstance()->SendNextPlayerNotification();
    }
}

void BLECentralGame::makeGuess(uint8_t playerId, uint8_t x, uint8_t y) {
    stopScanning();

    uint8_t currentPlayerId = _galaxis->getCurrentPlayerId();
    uint8_t guessResult = _galaxis->guess(playerId, x, y);
    uint8_t discovered = _galaxis->player(currentPlayerId)->getDiscovered();

    SendGuessResponse(currentPlayerId, guessResult, discovered);
    if (_galaxis->getGameState() == gameOver)
        SendGameOverNotification(currentPlayerId);
    else
        SendNextPlayerNotification();
}

void BLECentralGame::stopScanning() {
    if(_isScanning) {
        BLE.stopScan();
        _isScanning = false;
    }
}

void BLECentralGame::startScanning() {
    if (!_isScanning && _connectionCount < MAX_PERIPHERALS) {
        BLE.scanForUuid(GALAXIS_SERVICE_UUID, false);
        _isScanning = true;
    }
}

void BLECentralGame::SendGameOverNotification(uint8_t winner) const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = GAME_OVER;
    message.id = 0xff;
    message.param1 = winner;
    for (int i = 0; i < _connectionCount; ++i) {
        _galaxisCharacteristic[i].writeValue(&message, sizeof(GalaxisMessage), true);
    }
    notifyObservers(message);
}

void BLECentralGame::SendNextPlayerNotification() const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = NEXT;
    message.id = 0xff;
    message.param1 = _galaxis->getCurrentPlayerId();
    notifyObservers(message);
    for (int i = 0; i < _connectionCount; ++i) {
        _galaxisCharacteristic[i].writeValue(&message, sizeof(GalaxisMessage), true);
    }
}

void BLECentralGame::SendGuessResponse(uint8_t receiver, uint8_t guessResult, uint8_t discovered) const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = SEARCH;
    message.id = receiver;
    message.param1 = guessResult;
    message.param2 = discovered;
    notifyObservers(message);
    for (int i = 0; i < _connectionCount; ++i) {
        _galaxisCharacteristic[i].writeValue(&message, sizeof(GalaxisMessage), true);
    }
}

void BLECentralGame::NotifyUiConnected(bool connected) {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = CONNECT;
    message.id = 0;
    message.param1 = connected;
    message.param2 = 0;
    notifyObservers(message);
}
