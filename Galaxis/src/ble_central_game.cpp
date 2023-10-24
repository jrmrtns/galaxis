//
// Created by jmartens on 17.10.2023.
//

#include "ble_central_game.h"

BLECentralGame* BLECentralGame::_instance = nullptr;
BLEService galaxisHostService("{5A9AB000-CF0B-4281-BB4F-60C67E9ACC28}");
BLECharacteristic galaxisCharacteristic("5A9AB001-CF0B-4281-BB4F-60C67E9ACC28", BLERead | BLEWrite | BLENotify, sizeof (GalaxisMessage));

BLECentralGame::BLECentralGame() {
    _instance = this;
    _galaxis = std::unique_ptr<Galaxis>(new Galaxis(2, single_board, false));

    BLE.setLocalName("Galaxis");
    BLE.setAdvertisedService(galaxisHostService);
    galaxisHostService.addCharacteristic(galaxisCharacteristic);
    BLE.addService(galaxisHostService);

    BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
    BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
    galaxisCharacteristic.setEventHandler(BLEWritten, galaxisCharacteristicWritten);

    //galaxisCharacteristic.setValue(0, sizeof(GalaxisMessage));
    BLE.advertise();
}

BLECentralGame *BLECentralGame::getInstance() {
    return _instance;
}

// NOLINTNEXTLINE
void BLECentralGame::blePeripheralConnectHandler(BLEDevice central)  {
    Serial.print("Connected event, central: ");
    Serial.println(central.address());
}

// NOLINTNEXTLINE
void BLECentralGame::blePeripheralDisconnectHandler(BLEDevice central) {
    Serial.print("Disconnected event, central: ");
    Serial.println(central.address());
}

// NOLINTNEXTLINE
void BLECentralGame::galaxisCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
    GalaxisMessage galaxisMessage = {0};
    characteristic.readValue(&galaxisMessage, sizeof (galaxisMessage));
    if (galaxisMessage.msgType != REQUEST)
        return;

    if (galaxisMessage.command == SEARCH){
        BLECentralGame::getInstance()->makeGuess(galaxisMessage.id, galaxisMessage.param1, galaxisMessage.param2);
    }
}

void BLECentralGame::makeGuess(uint8_t playerId, uint8_t x, uint8_t y) {
    uint8_t currentPlayerId = _galaxis->getCurrentPlayerId();
    uint8_t guessResult = _galaxis->guess(playerId, x, y);
    uint8_t discovered = _galaxis->player(currentPlayerId)->getDiscovered();

    SendGuessResponse(currentPlayerId, guessResult, discovered);
    SendNextPlayerNotification(_galaxis->getCurrentPlayerId());
    if (_galaxis->getGameState() == gameOver)
        SendGameOverNotification(currentPlayerId);
}

void BLECentralGame::SendGameOverNotification(uint8_t winner) const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = GAME_OVER;
    message.id = 0xff;
    message.param1 = winner;
    notifyObservers(message);
}

void BLECentralGame::SendNextPlayerNotification(uint8_t nextPlayer) const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = NEXT;
    message.id = 0xff;
    message.param1 = nextPlayer;
    notifyObservers(message);
}

void BLECentralGame::SendGuessResponse(uint8_t receiver, uint8_t guessResult, uint8_t discovered) const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = SEARCH;
    message.id = receiver;
    message.param1 = guessResult;
    message.param2 = discovered;
    notifyObservers(message);
    galaxisCharacteristic.writeValue(&message, sizeof(GalaxisMessage), true);
}
