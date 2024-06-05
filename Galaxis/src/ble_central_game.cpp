//
// Created by jmartens on 25.10.2023.
//

#include "ble_central_game.h"
#include "settings.h"
#include <ArduinoBLE.h>
#include <memory>

BLECentralGame *BLECentralGame::_instance = nullptr;
std::vector<BLEDevice> BLECentralGame::devices;
uint8_t BLECentralGame::_connectionCount = 0;
bool BLECentralGame::_isScanning = false;
bool BLECentralGame::_gameStarted = false;

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

BLECentralGame *BLECentralGame::getInstance() {
    return _instance;
}

void BLECentralGame::discoverHandler(BLEDevice bleDevice) {
    if (!bleDevice.connect()) {
        return;
    }

    if (!bleDevice.discoverAttributes()) {
        bleDevice.disconnect();
        return;
    }

    BLECharacteristic characteristic = bleDevice.characteristic(GALAXIS_CHARACTERISTIC_UUID);
    characteristic.setEventHandler(BLEWritten, galaxisCharacteristicWritten);
    if (!characteristic || !characteristic.canSubscribe()) {
        bleDevice.disconnect();
        return;
    }

    devices.push_back(bleDevice);
    characteristic.subscribe();

    SendPairingMessage();

    startScanning();
}

// NOLINTNEXTLINE
void BLECentralGame::peripheralDisconnectHandler(BLEDevice bleDevice) {
    if (!_gameStarted)
        startScanning();

    for (auto it = devices.begin(); it != devices.end();) {
        if (*it == bleDevice) {
            uint8_t ct = std::distance(devices.begin(), it) + 1;
            getInstance()->_galaxis->remove(ct);
            it = devices.erase(it);
        } else {
            ++it;
        }
    }

    BLECentralGame::getInstance()->NotifyUiConnected(false);
}

// NOLINTNEXTLINE
void BLECentralGame::galaxisCharacteristicWritten(BLEDevice bleDevice, BLECharacteristic characteristic) {
    GalaxisMessage galaxisMessage = {0};
    characteristic.readValue(&galaxisMessage, sizeof(galaxisMessage));

    logMessage(galaxisMessage);

    if (galaxisMessage.msgType != REQUEST)
        return;

    if (galaxisMessage.command == SEARCH) {
        BLECentralGame::getInstance()->makeGuess(galaxisMessage.id, galaxisMessage.param1, galaxisMessage.param2);
    }

    if (galaxisMessage.command == NEXT) {
        BLECentralGame::getInstance()->SendNextPlayerNotification();
    }
}

void BLECentralGame::logMessage(const GalaxisMessage &galaxisMessage) {
    Serial.print(galaxisMessage.msgType);
    Serial.print(":");
    Serial.print(galaxisMessage.command);
    Serial.print(":");
    Serial.print(galaxisMessage.id);
    Serial.print(":");
    Serial.print(galaxisMessage.param1);
    Serial.print(":");
    Serial.println(galaxisMessage.param2);
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
    if (_isScanning) {
        BLE.stopScan();
        _isScanning = false;
    }
    _gameStarted = true;
}

void BLECentralGame::startScanning() {
    if (!_isScanning && _connectionCount < MAX_PLAYERS - 1) {
        BLE.scanForUuid(GALAXIS_SERVICE_UUID, false);
        _isScanning = true;
    }
}

void BLECentralGame::SendPairingMessage() {
    uint16_t id = getInstance()->_galaxis->join();
    GalaxisMessage message = {0};
    message.msgType = PAIRING_RESPONSE;
    message.command = CONNECT;
    message.id = 0;
    message.param1 = true;
    message.param2 = id;
    devices[_connectionCount]
        .characteristic(GALAXIS_CHARACTERISTIC_UUID)
        .writeValue(&message, sizeof(GalaxisMessage), true);
    _connectionCount++;
    getInstance()->NotifyUiConnected(true);
    getInstance()->NotifyUiClientConnected();
}

void BLECentralGame::SendGameOverNotification(uint8_t winner) const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = GAME_OVER;
    message.id = 0xff;
    message.param1 = winner;

    BLE.setEventHandler(BLEDisconnected, nullptr);

    for (auto &device: devices) {
        device.characteristic(GALAXIS_CHARACTERISTIC_UUID).writeValue(&message, sizeof(GalaxisMessage), true);
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
    for (auto &device: devices) {
        device.characteristic(GALAXIS_CHARACTERISTIC_UUID).writeValue(&message, sizeof(GalaxisMessage), true);
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
    for (auto &device: devices) {
        device.characteristic(GALAXIS_CHARACTERISTIC_UUID).writeValue(&message, sizeof(GalaxisMessage), true);
    }
}

void BLECentralGame::NotifyUiClientConnected() {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = CLIENT_CONNECTED;
    message.id = 0;
    message.param1 = _connectionCount;
    message.param2 = 0;
    notifyObservers(message);
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
