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

    BLE.setEventHandler(BLEDiscovered, discoverHandler);
    BLE.setEventHandler(BLEDisconnected, peripheralDisconnectHandler);
    BLE.scanForUuid(GALAXIS_SERVICE_UUID, false);
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

    _galaxisCharacteristic.subscribe();
}

void BLECentralGame::peripheralDisconnectHandler(BLEDevice central) {
    Serial.print("Disconnected event: ");
    Serial.println(central.address());
    BLE.scanForUuid(GALAXIS_SERVICE_UUID, false);
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

    if (galaxisMessage.msgType != RESPONSE)
        return;

    BLECentralGame::getInstance()->notifyObservers(galaxisMessage);
}

void BLECentralGame::makeGuess(uint8_t playerId, uint8_t x, uint8_t y) {
    GalaxisMessage message = {0};
    message.msgType = REQUEST;
    message.command = SEARCH;
    message.id = playerId;
    message.param1 = x;
    message.param2 = y;
    _galaxisCharacteristic.writeValue(&message, sizeof(GalaxisMessage));
}
