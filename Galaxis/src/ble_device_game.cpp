//
// Created by jmartens on 17.10.2023.
//

#include "ble_device_game.h"
#include "settings.h"

BLEDeviceGame* BLEDeviceGame::_instance = nullptr;
BLEService galaxisHostService(GALAXIS_SERVICE_UUID);
BLECharacteristic galaxisCharacteristic(GALAXIS_CHARACTERISTIC_UUID, BLERead | BLEWrite | BLENotify, sizeof (GalaxisMessage));

BLEDeviceGame::BLEDeviceGame() {
    _instance = this;

    BLE.setLocalName("Galaxis");
    galaxisHostService.addCharacteristic(galaxisCharacteristic);
    BLE.addService(galaxisHostService);
    BLE.setAdvertisedService(galaxisHostService);

    BLE.setEventHandler(BLEConnected, peripheralConnectHandler);
    BLE.setEventHandler(BLEDisconnected, peripheralDisconnectHandler);
    galaxisCharacteristic.setEventHandler(BLEWritten, galaxisCharacteristicWritten);
    galaxisCharacteristic.setEventHandler(BLESubscribed, galaxisCharacteristicSubscribed);

    BLE.advertise();
}

BLEDeviceGame *BLEDeviceGame::getInstance() {
    return _instance;
}

// NOLINTNEXTLINE
void BLEDeviceGame::peripheralConnectHandler(BLEDevice central)  {
    Serial.print("Connected event, central: ");
    Serial.println(central.address());
}

// NOLINTNEXTLINE
void BLEDeviceGame::peripheralDisconnectHandler(BLEDevice central) {
    Serial.print("Disconnected event, central: ");
    Serial.println(central.address());
}

// NOLINTNEXTLINE
void BLEDeviceGame::galaxisCharacteristicSubscribed(BLEDevice central, BLECharacteristic characteristic) {
    Serial.print("Subscribed event, central: ");
    Serial.println(central.address());

    GalaxisMessage message = {0};
    message.msgType = REQUEST;
    message.command = NEXT;
    message.id = 0x00;
    message.param1 = 0x00;
    message.param2 = 0x00;
    galaxisCharacteristic.writeValue(&message, sizeof(GalaxisMessage));
}

// NOLINTNEXTLINE
void BLEDeviceGame::galaxisCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
    GalaxisMessage galaxisMessage = {0};
    characteristic.readValue(&galaxisMessage, sizeof (galaxisMessage));

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

    BLEDeviceGame::getInstance()->notifyObservers(galaxisMessage);
}

void BLEDeviceGame::makeGuess(uint8_t playerId, uint8_t x, uint8_t y) {
    GalaxisMessage message = {0};
    message.msgType = REQUEST;
    message.command = SEARCH;
    message.id = playerId;
    message.param1 = x;
    message.param2 = y;
    galaxisCharacteristic.writeValue(&message, sizeof(GalaxisMessage));
}
