//
// Created by jmartens on 19.10.2023.
//

#ifndef GALAXIS_SETTINGS_H
#define GALAXIS_SETTINGS_H

#ifdef WS
#define PIN_ENC_IN1 16
#define PIN_ENC_IN2 15
#define PIN_ENC_GROUND 17
#define PIN_ENC_BUTTON 18
#elif ARDUINO_M5Stack_StampS3
#define PIN_ENC_IN1 41
#define PIN_ENC_IN2 40
#define PIN_ENC_BUTTON 42
#define PIN_TONE_OUTPUT 3
#else
#define PIN_ENC_IN1 D1
#define PIN_ENC_IN2 D0
#define PIN_ENC_GROUND D2
#define PIN_ENC_BUTTON D3
#define PIN_TONE_OUTPUT D4;
#endif

#define MAX_X 9
#define MAX_Y 7
#define SHIP_COUNT 4

#define GALAXIS_SERVICE_UUID "5A9AB000-CF0B-4281-BB4F-60C67E9ACC28"
#define GALAXIS_CHARACTERISTIC_UUID "5A9AB001-CF0B-4281-BB4F-60C67E9ACC28"

#ifdef DE
#define START_MESSAGE "Du bist dran"
#define WAITING_FOR_PLAYER "Warte auf Spieler "
#define CONNECTING "Verbinde ..."
#define PLAYER "Spieler "
#define GAME_OVER_MESSAGE "Game over"
#define GAME_OVER_HINT "Nochmal spielen?"
#define GAME_OVER_WINNER_MESSAGE "Gewinner"
#define GAME_OVER_WINNER_HINT "Nochmal spielen?"
#define MAIN_MENU_SINGLE "Einzel";
#define MAIN_MENU_SINGLE_HINT "Einzelspiel";
#define MAIN_MENU_NEW_GAME "Neu";
#define MAIN_MENU_NEW_GAME_HINT "Neues Spiel starten";
#define MAIN_MENU_JOIN "Join";
#define MAIN_MENU_JOIN_HINT "Einem Spiel beitreten";
#define MAIN_MENU_OFF "Off";
#else
#define START_MESSAGE "Start..."
#define WAITING_FOR_PLAYER "Waiting for player "
#define CONNECTING "Connecting ..."
#define PLAYER "Player "
#define GAME_OVER_MESSAGE "Game over"
#define GAME_OVER_HINT "Press button for new game"
#define GAME_OVER_WINNER_MESSAGE "** You Won **"
#define GAME_OVER_WINNER_HINT "Press button for new game"
#define MAIN_MENU_SINGLE "Single";
#define MAIN_MENU_SINGLE_HINT "Singleplayer game";
#define MAIN_MENU_NEW_GAME "New";
#define MAIN_MENU_NEW_GAME_HINT "Start new game";
#define MAIN_MENU_JOIN "Join";
#define MAIN_MENU_JOIN_HINT "Join a game";
#define MAIN_MENU_OFF "Off";
#endif

const float conversion_factor = 3.3f / (1 << 12) * 3;

#endif //GALAXIS_SETTINGS_H
