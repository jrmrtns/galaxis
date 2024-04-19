// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: Galaxis

#ifndef _GALAXIS_UI_H
#define _GALAXIS_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "ui_events.h"
// SCREEN: ui_SplashScreen
void ui_SplashScreen_screen_init(void);
extern lv_obj_t * ui_SplashScreen;
extern lv_obj_t * ui_SplashLabel;
// SCREEN: ui_MainMenu
void ui_MainMenu_screen_init(void);
extern lv_obj_t * ui_MainMenu;
extern lv_obj_t * ui_MainMenuItem;
extern lv_obj_t * ui_MainMenuHint;
// SCREEN: ui_Game
void ui_Game_screen_init(void);
extern lv_obj_t * ui_Game;
extern lv_obj_t * ui_SearchResult;
extern lv_obj_t * ui_Coordinates;
extern lv_obj_t * ui_StatusLabel;
extern lv_obj_t * ui_Connected;
// SCREEN: ui_GameOver
void ui_GameOver_screen_init(void);
extern lv_obj_t * ui_GameOver;
extern lv_obj_t * ui_GameOverItem;
extern lv_obj_t * ui_GameOverHint;
extern lv_obj_t * ui____initial_actions0;

LV_IMG_DECLARE(ui_img_bg_png);    // assets\bg.png
LV_IMG_DECLARE(ui_img_682575846);    // assets\_55fb20de-87ae-4109-bf2d-083075e9aa51.png
LV_IMG_DECLARE(ui_img_wifi_png);    // assets\wifi.png

LV_FONT_DECLARE(ui_font_Destruct36);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
