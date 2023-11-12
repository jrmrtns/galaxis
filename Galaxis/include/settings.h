//
// Created by jmartens on 19.10.2023.
//

#ifndef GALAXIS_SETTINGS_H
#define GALAXIS_SETTINGS_H

#define PIN_ENC_IN1 D1
#define PIN_ENC_IN2 D0
#define PIN_ENC_GROUND D2
#define PIN_ENC_BUTTON D3

#define MAX_X 9
#define MAX_Y 7
#define SHIP_COUNT 4

#define GALAXIS_SERVICE_UUID "5A9AB000-CF0B-4281-BB4F-60C67E9ACC28"
#define GALAXIS_CHARACTERISTIC_UUID "5A9AB001-CF0B-4281-BB4F-60C67E9ACC28"

#define START_MESSAGE "Los gehts"
#define WAITING_FOR_PLAYER "Warte auf Spieler "
#define CONNECTING "Verbinde ..."
#define PLAYER "Spieler "
#define GAME_OVER_MESSAGE "Game over"
#define MAIN_MENU_SINGLE "Einzel";
#define MAIN_MENU_SINGLE_HINT "Einzelspiel";
#define MAIN_MENU_NEW_GAME "Neu";
#define MAIN_MENU_NEW_GAME_HINT "Neues Spiel starten";
#define MAIN_MENU_JOIN "Join";
#define MAIN_MENU_JOIN_HINT "Einem Spiel beitreten";
#define MAIN_MENU_OFF "Off";

#endif //GALAXIS_SETTINGS_H
