// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: Galaxis

#include "../ui.h"

void ui_Game_screen_init(void)
{
    ui_Game = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Game, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Game, lv_color_hex(0x1E1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Game, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Game, lv_color_hex(0x4183FC), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_Game, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_GamePanel = lv_obj_create(ui_Game);
    lv_obj_set_width(ui_GamePanel, 220);
    lv_obj_set_height(ui_GamePanel, 220);
    lv_obj_set_align(ui_GamePanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_GamePanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_GamePanel, 110, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_GamePanel, &ui_img_bg2_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Connected = lv_img_create(ui_GamePanel);
    lv_img_set_src(ui_Connected, &ui_img_wifi_png);
    lv_obj_set_width(ui_Connected, LV_SIZE_CONTENT);   /// 16
    lv_obj_set_height(ui_Connected, LV_SIZE_CONTENT);    /// 16
    lv_obj_set_x(ui_Connected, 0);
    lv_obj_set_y(ui_Connected, -42);
    lv_obj_set_align(ui_Connected, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Connected, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Connected, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_opa(ui_Connected, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StatusLabel = lv_label_create(ui_GamePanel);
    lv_obj_set_width(ui_StatusLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_StatusLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_StatusLabel, 2);
    lv_obj_set_y(ui_StatusLabel, 38);
    lv_obj_set_align(ui_StatusLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_StatusLabel, "Connecting ...");
    lv_obj_set_style_bg_color(ui_StatusLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_StatusLabel, 148, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SearchResult = lv_label_create(ui_GamePanel);
    lv_obj_set_width(ui_SearchResult, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SearchResult, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SearchResult, -1);
    lv_obj_set_y(ui_SearchResult, -11);
    lv_obj_set_align(ui_SearchResult, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SearchResult, "-");
    lv_obj_set_style_text_color(ui_SearchResult, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SearchResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SearchResult, &ui_font_Destruct36, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_SearchResult, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SearchResult, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SearchResult, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SearchResult, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SearchResult, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SearchResult, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SearchResult, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CoordinatesX = lv_label_create(ui_GamePanel);
    lv_obj_set_width(ui_CoordinatesX, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CoordinatesX, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CoordinatesX, -76);
    lv_obj_set_y(ui_CoordinatesX, 3);
    lv_obj_set_align(ui_CoordinatesX, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CoordinatesX, "A");
    lv_obj_set_style_text_color(ui_CoordinatesX, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CoordinatesX, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_CoordinatesX, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_CoordinatesX, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_CoordinatesX, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CoordinatesX, &ui_font_Destruct24, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CoordinatesY = lv_label_create(ui_GamePanel);
    lv_obj_set_width(ui_CoordinatesY, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CoordinatesY, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CoordinatesY, 72);
    lv_obj_set_y(ui_CoordinatesY, 3);
    lv_obj_set_align(ui_CoordinatesY, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CoordinatesY, "1");
    lv_obj_set_style_text_color(ui_CoordinatesY, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CoordinatesY, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_CoordinatesY, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_CoordinatesY, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_CoordinatesY, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CoordinatesY, &ui_font_Destruct24, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Coordinates = lv_label_create(ui_GamePanel);
    lv_obj_set_width(ui_Coordinates, lv_pct(100));
    lv_obj_set_height(ui_Coordinates, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Coordinates, 0);
    lv_obj_set_y(ui_Coordinates, 2);
    lv_obj_set_align(ui_Coordinates, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Coordinates, "");
    lv_obj_set_style_text_color(ui_Coordinates, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Coordinates, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Coordinates, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Coordinates, &ui_font_Destruct24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Coordinates, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Coordinates, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_Coordinates, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Coordinates, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Coordinates, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Coordinates, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Coordinates, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

}
