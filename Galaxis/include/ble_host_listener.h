//
// Created by jmartens on 17.10.2023.
//

#ifndef GALAXIS_BLE_HOST_LISTENER_H
#define GALAXIS_BLE_HOST_LISTENER_H

#include "subject.h"
#include <ArduinoBLE.h>

class BLE_HostListener: public Subject {
protected:
    BLE_HostListener();

public:
    static BLE_HostListener *getInstance();

private:
    static BLE_HostListener *_instance;
    static void blePeripheralConnectHandler(BLEDevice central);
    static void blePeripheralDisconnectHandler(BLEDevice central);
    static void galaxisCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic);
};

#endif //GALAXIS_BLE_HOST_LISTENER_H
