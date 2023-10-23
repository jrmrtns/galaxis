//
// Created by jmartens on 17.10.2023.
//

#include "ble_central_game.h"

BLECentralGame* BLECentralGame::_instance = nullptr;
BLEService galaxisHostService("{5A9AB000-CF0B-4281-BB4F-60C67E9ACC28}");
BLECharacteristic galaxisCharacteristic("5A9AB001-CF0B-4281-BB4F-60C67E9ACC28", BLERead | BLEWrite | BLEIndicate, sizeof (GalaxisMessage));

BLECentralGame::BLECentralGame() {
    _galaxis = std::unique_ptr<Galaxis>(new Galaxis(2, single_board, false));

    BLE.setLocalName("Galaxis");
    BLE.setAdvertisedService(galaxisHostService);
    galaxisHostService.addCharacteristic(galaxisCharacteristic);
    BLE.addService(galaxisHostService);

    BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
    BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
    galaxisCharacteristic.setEventHandler(BLEWritten, galaxisCharacteristicWritten);

    BLE.advertise();
}

BLECentralGame *BLECentralGame::getInstance() {
    if (_instance == nullptr)
        _instance = new BLECentralGame();
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
        BLECentralGame::getInstance()->makeRemoteGuess(galaxisMessage.id, galaxisMessage.param1, galaxisMessage.param2);
    }
}

void BLECentralGame::makeGuess(uint8_t playerId, uint8_t x, uint8_t y) {
    _galaxis->dumpCurrent();
    uint8_t currentPlayer = _galaxis->getCurrentPlayer();
    uint8_t guessResult = _galaxis->guess(playerId, x, y);
    SendGuessResponse(currentPlayer, guessResult);
    SendNextPlayerNotification(_galaxis->getCurrentPlayer());
    if (_galaxis->getGameState() == gameOver)
        SendGameOverNotification(currentPlayer);
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
    Serial.println(nextPlayer);
    message.param1 = nextPlayer;
    notifyObservers(message);
}

void BLECentralGame::SendGuessResponse(uint8_t receiver, uint8_t guessResult) const {
    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = SEARCH;
    message.id = receiver;
    message.param1 = guessResult;
    notifyObservers(message);
}

void BLECentralGame::makeRemoteGuess(uint8_t playerId, uint8_t x, uint8_t y) {
    _galaxis->dumpCurrent();

    uint8_t currentPlayer = _galaxis->getCurrentPlayer();
    uint8_t guessResult = _galaxis->guess(playerId, x, y);

    GalaxisMessage message = {0};
    message.msgType = RESPONSE;
    message.command = SEARCH;
    message.id = playerId;
    message.param1 = guessResult;

    galaxisCharacteristic.writeValue(&message, sizeof(GalaxisMessage), false);
}


