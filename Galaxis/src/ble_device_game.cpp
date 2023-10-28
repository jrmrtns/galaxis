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
    _galaxis = std::unique_ptr<Galaxis>(new Galaxis(2, single_board, false));

    BLE.setLocalName("Galaxis");
    galaxisHostService.addCharacteristic(galaxisCharacteristic);
    BLE.addService(galaxisHostService);
    BLE.setAdvertisedService(galaxisHostService);

    BLE.setEventHandler(BLEConnected, peripheralConnectHandler);
    BLE.setEventHandler(BLEDisconnected, peripheralDisconnectHandler);
    galaxisCharacteristic.setEventHandler(BLEWritten, galaxisCharacteristicWritten);
    galaxisCharacteristic.setEventHandler(BLESubscribed, galaxisCharacteristicSubscribed);

    //galaxisCharacteristic.setValue(0, sizeof(GalaxisMessage));
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
    Serial.print("Subscribed event, central: ");
    Serial.println(central.address());
    BLEDeviceGame::getInstance()->SendNextPlayerNotification();
}

// NOLINTNEXTLINE
void BLEDeviceGame::galaxisCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
    GalaxisMessage galaxisMessage = {0};
    characteristic.readValue(&galaxisMessage, sizeof (galaxisMessage));
    if (galaxisMessage.msgType != REQUEST)
        return;

    if (galaxisMessage.command == SEARCH){
        BLEDeviceGame::getInstance()->makeGuess(galaxisMessage.id, galaxisMessage.param1, galaxisMessage.param2);
    }
}

void BLEDeviceGame::makeGuess(uint8_t playerId, uint8_t x, uint8_t y) {
    uint8_t currentPlayerId = _galaxis->getCurrentPlayerId();
    uint8_t guessResult = _galaxis->guess(playerId, x, y);
    uint8_t discovered = _galaxis->player(currentPlayerId)->getDiscovered();

    SendGuessResponse(currentPlayerId, guessResult, discovered);
    SendNextPlayerNotification();
    if (_galaxis->getGameState() == gameOver)
        SendGameOverNotification(currentPlayerId);
}

void BLEDeviceGame::SendGameOverNotification(uint8_t winner) const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = GAME_OVER;
    message.id = 0xff;
    message.param1 = winner;
    notifyObservers(message);
    galaxisCharacteristic.writeValue(&message, sizeof(GalaxisMessage), true);
}

void BLEDeviceGame::SendNextPlayerNotification() const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = NEXT;
    message.id = 0xff;
    message.param1 = _galaxis->getCurrentPlayerId();
    notifyObservers(message);
    galaxisCharacteristic.writeValue(&message, sizeof(GalaxisMessage), true);
}

void BLEDeviceGame::SendGuessResponse(uint8_t receiver, uint8_t guessResult, uint8_t discovered) const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = SEARCH;
    message.id = receiver;
    message.param1 = guessResult;
    message.param2 = discovered;
    notifyObservers(message);
    galaxisCharacteristic.writeValue(&message, sizeof(GalaxisMessage), true);
}
