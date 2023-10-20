//
// Created by jmartens on 17.10.2023.
//

#include "ble_host_listener.h"
#include <ui.h>

BLE_HostListener* BLE_HostListener::_instance = nullptr;
BLEService galaxisHostService("{5A9AB000-CF0B-4281-BB4F-60C67E9ACC28}"); // create service
BLEByteCharacteristic galaxisCharacteristic("5A9AB001-CF0B-4281-BB4F-60C67E9ACC28", BLERead | BLEWrite | BLEIndicate);

BLE_HostListener::BLE_HostListener() {
    BLE.setLocalName("Galaxis");
    BLE.setAdvertisedService(galaxisHostService);
    galaxisHostService.addCharacteristic(galaxisCharacteristic);
    BLE.addService(galaxisHostService);

    BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
    BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
    galaxisCharacteristic.setEventHandler(BLEWritten, galaxisCharacteristicWritten);
    galaxisCharacteristic.setValue(0);

    BLE.advertise();
}

BLE_HostListener *BLE_HostListener::getInstance() {
    if (_instance == nullptr)
        _instance = new BLE_HostListener();
    return _instance;
}

void BLE_HostListener::blePeripheralConnectHandler(BLEDevice central) {
    Serial.print("Connected event, central: ");
    Serial.println(central.address());
}

void BLE_HostListener::blePeripheralDisconnectHandler(BLEDevice central) {
    Serial.print("Disconnected event, central: ");
    Serial.println(central.address());
}

void BLE_HostListener::galaxisCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
    Serial.print("Characteristic event, written: ");
    Serial.println(central.address());

    //GalaxisMessage galaxisMessage;
    //memcpy(&galaxisMessage, incomingData, sizeof(galaxisMessage));

    if (characteristic.value()) {
        //_ui_state_modify( ui_GamePanel, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
        //lv_event_send(ui_GamePanel, LV_EVENT_VALUE_CHANGED, nullptr);
        _ui_state_modify( ui_Game, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
    } else {
        //_ui_state_modify( ui_GamePanel, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        //lv_event_send(ui_GamePanel, LV_EVENT_VALUE_CHANGED, nullptr);
        _ui_state_modify( ui_Game, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
    }
}
