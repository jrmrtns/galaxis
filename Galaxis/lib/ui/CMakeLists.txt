SET(SOURCES screens/ui_SplashScreen.c
    screens/ui_MainMenu.c
    screens/ui_Game.c
    screens/ui_GameOver.c
    screens/ui_Settings.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.cpp
    images/ui_img_bg_png.c
    images/ui_img_bg2_png.c
    images/ui_img_wifi_png.c
    fonts/ui_font_Destruct24.c
    fonts/ui_font_Destruct36.c)

add_library(ui ${SOURCES})
