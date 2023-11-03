SET(SOURCES screens/ui_SplashScreen.c
    screens/ui_MainMenu.c
    screens/ui_Game.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_bg_png.c
    images/ui_img_wifi_png.c
    fonts/ui_font_Destruct36.c)

add_library(ui ${SOURCES})
