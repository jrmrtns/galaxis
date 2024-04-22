// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: Galaxis

#include "../ui.h"

void ui_MainMenu_screen_init(void)
{
    ui_MainMenu = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_MainMenu, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MainMenu, lv_color_hex(0xBAD6E1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MainMenu, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_MainMenu, &ui_img_682575846, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MainMenuItem = lv_label_create(ui_MainMenu);
    lv_obj_set_width(ui_MainMenuItem, lv_pct(100));
    lv_obj_set_height(ui_MainMenuItem, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MainMenuItem, 0);
    lv_obj_set_y(ui_MainMenuItem, -1);
    lv_obj_set_align(ui_MainMenuItem, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MainMenuItem, "Einzel");
    lv_obj_set_style_text_color(ui_MainMenuItem, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MainMenuItem, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_MainMenuItem, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_MainMenuItem, &ui_font_Destruct36, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MainMenuItem, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MainMenuItem, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_MainMenuItem, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_MainMenuItem, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_MainMenuItem, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_MainMenuItem, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MainMenuHint = lv_label_create(ui_MainMenu);
    lv_obj_set_width(ui_MainMenuHint, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MainMenuHint, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MainMenuHint, 0);
    lv_obj_set_y(ui_MainMenuHint, 38);
    lv_obj_set_align(ui_MainMenuHint, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MainMenuHint, "");
    lv_obj_set_style_bg_color(ui_MainMenuHint, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MainMenuHint, 150, LV_PART_MAIN | LV_STATE_DEFAULT);

}
