#include "hide_ships_view.h"

#include "RotaryEncoder.h"
#include "core/lv_disp.h"
#include "screens/ui_HideShips.h"
#include "widgets/lv_label.h"

HideShipsView::HideShipsView(RotaryEncoder* encoder) : IView(), _encoder(encoder)
{
}

void HideShipsView::setFocus(int position)
{
    _focusedElement = position % 5;
    if (_focusedElement == 0)
    {
        lv_obj_add_state(ui_Ship1, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_Ship2, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_Ship3, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_Ship4, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_okButton1, LV_STATE_FOCUSED);
    }
    if (_focusedElement == 1)
    {
        lv_obj_clear_state(ui_Ship1, LV_STATE_FOCUSED);
        lv_obj_add_state(ui_Ship2, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_Ship3, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_Ship4, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_okButton1, LV_STATE_FOCUSED);
    }
    if (_focusedElement == 2)
    {
        lv_obj_clear_state(ui_Ship1, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_Ship2, LV_STATE_FOCUSED);
        lv_obj_add_state(ui_Ship3, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_Ship4, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_okButton1, LV_STATE_FOCUSED);
    }
    if (_focusedElement == 3)
    {
        lv_obj_clear_state(ui_Ship1, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_Ship2, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_Ship3, LV_STATE_FOCUSED);
        lv_obj_add_state(ui_Ship4, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_okButton1, LV_STATE_FOCUSED);
    }
    if (_focusedElement == 4)
    {
        lv_obj_clear_state(ui_Ship1, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_Ship2, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_Ship3, LV_STATE_FOCUSED);
        lv_obj_clear_state(ui_Ship4, LV_STATE_FOCUSED);
        lv_obj_add_state(ui_okButton1, LV_STATE_FOCUSED);

        auto c = lv_label_get_text(ui_okButtonLabel1);
    }
}

Screen HideShipsView::loop()
{
    int position = _encoder->getPosition();
    if (_lastPosition != position)
    {
        _lastPosition = position;
        setFocus(position);
    }
    return Screen::NO_CHANGE;
}

void HideShipsView::show()
{
    lv_scr_load_anim(ui_HideShips, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}
