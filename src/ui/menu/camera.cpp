#include "ui/menu/camera.h"

static MyCard mycardMenuBasic;

static void menu_camera_construct(lv_obj_t *parent) {
  /*
  lv_obj_set_width(parent, 300);
  lv_obj_set_height(parent, 200);
  lv_obj_set_x(parent, 10);
  lv_obj_set_y(parent, 48);
*/
  lv_obj_clear_flag(parent, LV_OBJ_FLAG_SCROLLABLE); /// Flags
  lv_obj_set_style_text_font(parent, &ui_font_chinese_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Roller3 = lv_roller_create(parent);
  lv_roller_set_options(ui_Roller3,
                        "白热\n黑热\n融合1\n融合2\n彩虹\n铁红1\n铁红2\n深褐色\n"
                        "色彩1\n色彩2\n冰火\n雨\n红热\n绿热\n深蓝",
                        LV_ROLLER_MODE_INFINITE);
  lv_obj_set_width(ui_Roller3, 85);
  lv_obj_set_height(ui_Roller3, 132);
  lv_obj_set_x(ui_Roller3, 95);
  lv_obj_set_y(ui_Roller3, 38);
  lv_obj_set_align(ui_Roller3, LV_ALIGN_TOP_MID);

  lv_obj_set_style_bg_opa(parent, 192, 0);
  lv_obj_set_style_border_width(parent, 0, 0);
  // lv_obj_set_style_bg_opa(ui_Checkbox1, 192, LV_PART_INDICATOR);
  // lv_obj_set_style_bg_opa(ui_Checkbox2, 192, LV_PART_INDICATOR);
  // lv_obj_set_style_bg_opa(ui_Checkbox3, 192, LV_PART_INDICATOR);
  // lv_obj_set_style_bg_opa(ui_Checkbox4, 192, LV_PART_INDICATOR);
  // lv_obj_set_style_bg_opa(ui_Checkbox5, 192, LV_PART_INDICATOR);
  // lv_obj_set_style_bg_opa(ui_Roller1, 192, 0);
  // lv_obj_set_style_bg_opa(ui_Roller2, 192, 0);
  // lv_obj_set_style_bg_opa(ui_Roller3, 192, 0);

  // 设置回调
  lv_obj_add_event_cb(
      ui_Roller3,
      [](lv_event_t *e) {
        globalSettings.colorPalette = lv_roller_get_selected(e->target);
      },
      LV_EVENT_KEY, NULL); // 颜色

  // 当前设置
  lv_roller_set_selected(ui_Roller3, globalSettings.colorPalette, LV_ANIM_OFF);
}

void menu_camera_show() {
  mycardMenuBasic.create(lv_layer_top(), 0, MENU_CAMERA_CARD_POS_Y,
                         MENU_CAMERA_CARD_WIDTH, MENU_CAMERA_CARD_HEIGHT,
                         LV_ALIGN_TOP_MID);
  menu_camera_construct(mycardMenuBasic.obj);
  lv_group_focus_obj(lv_obj_get_child(mycardMenuBasic.obj, 0));
  mycardMenuBasic.show();
}

void menu_camera_hide() {
  mycardMenuBasic.del();
  settings_save();
}
