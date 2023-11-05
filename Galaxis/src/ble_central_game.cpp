//
// Created by jmartens on 25.10.2023.
//

#include "ble_central_game.h"
#include "settings.h"
#include <ArduinoBLE.h>

BLECentralGame *BLECentralGame::_instance = nullptr;
BLECharacteristic BLECentralGame::_galaxisCharacteristic;

BLECentralGame::BLECentralGame() {
    _instance = this;

    _galaxis = std::unique_ptr<Galaxis>(new Galaxis(2, single_board, false));

    BLE.setEventHandler(BLEDiscovered, discoverHandler);
    BLE.setEventHandler(BLEDisconnected, peripheralDisconnectHandler);
    BLE.scanForUuid(GALAXIS_SERVICE_UUID, false);
}

BLECentralGame::~BLECentralGame() {
    _instance = nullptr;
}

void BLECentralGame::shutdown() {
    BLE.disconnect();
    BLE.stopScan();
    removeAllObservers();
    //BLE.end();
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

    _galaxisCharacteristic = peripheral.characteristic(GALAXIS_CHARACTERISTIC_UUID);
    _galaxisCharacteristic.setEventHandler(BLEWritten, galaxisCharacteristicWritten);
    if (!_galaxisCharacteristic || !_galaxisCharacteristic.canSubscribe()) {
        peripheral.disconnect();
        return;
    }

    BLECentralGame::getInstance()->NotifyUiConnected(true);

    _galaxisCharacteristic.subscribe();
}

void BLECentralGame::peripheralDisconnectHandler(BLEDevice central) {
    Serial.print("Disconnected event: ");
    Serial.println(central.address());
    BLE.scanForUuid(GALAXIS_SERVICE_UUID, false);
    BLECentralGame::getInstance()->NotifyUiConnected(false);
}

// NOLINTNEXTLINE
void BLECentralGame::galaxisCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
    GalaxisMessage galaxisMessage = {0};
    characteristic.readValue(&galaxisMessage, sizeof(galaxisMessage));

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

    if (galaxisMessage.command == SEARCH){
        BLECentralGame::getInstance()->makeGuess(galaxisMessage.id, galaxisMessage.param1, galaxisMessage.param2);
    }

    if (galaxisMessage.command == NEXT){
        BLECentralGame::getInstance()->SendNextPlayerNotification();
    }
}

void BLECentralGame::makeGuess(uint8_t playerId, uint8_t x, uint8_t y) {
    uint8_t currentPlayerId = _galaxis->getCurrentPlayerId();
    uint8_t guessResult = _galaxis->guess(playerId, x, y);
    uint8_t discovered = _galaxis->player(currentPlayerId)->getDiscovered();

    SendGuessResponse(currentPlayerId, guessResult, discovered);
    if (_galaxis->getGameState() == gameOver)
        SendGameOverNotification(currentPlayerId);
    else
        SendNextPlayerNotification();
}

void BLECentralGame::SendGameOverNotification(uint8_t winner) const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = GAME_OVER;
    message.id = 0xff;
    message.param1 = winner;
    _galaxisCharacteristic.writeValue(&message, sizeof(GalaxisMessage), true);
    notifyObservers(message);
}

void BLECentralGame::SendNextPlayerNotification() const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = NEXT;
    message.id = 0xff;
    message.param1 = _galaxis->getCurrentPlayerId();
    notifyObservers(message);
    _galaxisCharacteristic.writeValue(&message, sizeof(GalaxisMessage), true);
}

void BLECentralGame::SendGuessResponse(uint8_t receiver, uint8_t guessResult, uint8_t discovered) const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = SEARCH;
    message.id = receiver;
    message.param1 = guessResult;
    message.param2 = discovered;
    notifyObservers(message);
    _galaxisCharacteristic.writeValue(&message, sizeof(GalaxisMessage), true);
}

void BLECentralGame::NotifyUiConnected(bool connected) {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = CONNECTED;
    message.id = 0;
    message.param1 = connected;
    message.param2 = 0;
    notifyObservers(message);
}
