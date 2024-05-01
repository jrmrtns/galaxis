// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: Galaxis

#include "../ui.h"

void ui_SplashScreen_screen_init(void)
{
    ui_SplashScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SplashScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_SplashScreen, &ui_img_bg_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SplashLabel = lv_label_create(ui_SplashScreen);
    lv_obj_set_width(ui_SplashLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SplashLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SplashLabel, 0);
    lv_obj_set_y(ui_SplashLabel, -25);
    lv_obj_set_align(ui_SplashLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SplashLabel, "Galaxis");
    lv_obj_set_style_text_font(ui_SplashLabel, &ui_font_Destruct36, LV_PART_MAIN | LV_STATE_DEFAULT);

}
