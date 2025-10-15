#include "ui/menu/camera.h"

static MyCard mycardMenuBasic;

lv_obj_t *ui_Label7;
lv_obj_t *ui_Slider3;
lv_obj_t *ui_Label12;
lv_obj_t *ui_Slider5;
lv_obj_t *ui_Label14;
lv_obj_t *ui_Slider6;
lv_obj_t *ui_Slider4;

static void set_disable(lv_obj_t *obj) {
  lv_obj_set_style_bg_opa(obj, LV_OPA_10, LV_PART_MAIN | LV_STATE_DISABLED);
  lv_obj_add_state(obj, LV_STATE_DISABLED);
  lv_obj_update_layout(obj);
}

static void set_enable(lv_obj_t *obj) {
  lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DISABLED);
  lv_obj_clear_state(obj, LV_STATE_DISABLED);
  lv_obj_update_layout(obj);
}

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

  lv_obj_t *ui_Slider1 = lv_slider_create(parent);
  lv_obj_set_width(ui_Slider1, 128);
  lv_obj_set_height(ui_Slider1, 16);
  lv_obj_set_x(ui_Slider1, -20);
  lv_obj_set_y(ui_Slider1, 0);
  lv_obj_set_align(ui_Slider1, LV_ALIGN_TOP_MID);
  lv_obj_t *ui_Label1 = lv_label_create(ui_Slider1);
  lv_label_set_text(ui_Label1, "0%");
  lv_obj_align_to(ui_Label1, ui_Slider1, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0xFFFFFF),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_t *ui_Label2 = lv_label_create(parent);
  lv_label_set_text(ui_Label2, "亮度");
  lv_obj_align_to(ui_Label2, ui_Slider1, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  lv_obj_t *ui_Slider2 = lv_slider_create(parent);
  lv_obj_set_width(ui_Slider2, 128);
  lv_obj_set_height(ui_Slider2, 16);
  lv_obj_set_x(ui_Slider2, -20);
  lv_obj_set_y(ui_Slider2, 30);
  lv_obj_set_align(ui_Slider2, LV_ALIGN_TOP_MID);
  lv_obj_t *ui_Label3 = lv_label_create(ui_Slider2);
  lv_label_set_text(ui_Label3, "0%");
  lv_obj_align_to(ui_Label3, ui_Slider2, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0xFFFFFF),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_t *ui_Label4 = lv_label_create(parent);
  lv_label_set_text(ui_Label4, "对比度");
  lv_obj_align_to(ui_Label4, ui_Slider2, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  lv_obj_t *ui_Dropdown1 = lv_dropdown_create(parent);
  lv_dropdown_set_options(ui_Dropdown1, "关闭\n"
                                        "普通模式\n"
                                        "专家模式");
  lv_obj_set_width(ui_Dropdown1, 100);
  lv_obj_set_height(ui_Dropdown1, 30);
  lv_obj_set_x(ui_Dropdown1, -10);
  lv_obj_set_y(ui_Dropdown1, 60);
  lv_obj_set_align(ui_Dropdown1, LV_ALIGN_TOP_MID);
  lv_obj_set_style_pad_top(ui_Dropdown1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(ui_Dropdown1, 8, LV_PART_INDICATOR);
  lv_obj_set_style_text_font(ui_Dropdown1, &ui_font_chinese_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_Dropdown1, &lv_font_montserrat_14,
                             LV_PART_INDICATOR); // 箭头使用符号字体
  lv_obj_set_style_text_font(lv_dropdown_get_list(ui_Dropdown1),
                             &ui_font_chinese_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_t *ui_Label10 = lv_label_create(parent);
  lv_label_set_text(ui_Label10, "数字降噪");
  lv_obj_align_to(ui_Label10, ui_Dropdown1, LV_ALIGN_OUT_LEFT_MID, -15, 0);

  ui_Slider3 = lv_slider_create(parent);
  lv_obj_set_width(ui_Slider3, 96);
  lv_obj_set_height(ui_Slider3, 10);
  lv_obj_set_x(ui_Slider3, -10);
  lv_obj_set_y(ui_Slider3, 100);
  lv_obj_set_align(ui_Slider3, LV_ALIGN_TOP_MID);
  lv_obj_t *ui_Label6 = lv_label_create(ui_Slider3);
  lv_label_set_text(ui_Label6, "0%");
  lv_obj_align_to(ui_Label6, ui_Slider3, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_color(ui_Label6, lv_color_hex(0xFFFFFF),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  ui_Label7 = lv_label_create(parent);
  lv_label_set_text(ui_Label7, "降噪等级");
  lv_obj_align_to(ui_Label7, ui_Slider3, LV_ALIGN_OUT_LEFT_MID, -10, 0);

  ui_Slider5 = lv_slider_create(parent);
  lv_obj_set_width(ui_Slider5, 50);
  lv_obj_set_height(ui_Slider5, 10);
  lv_obj_set_x(ui_Slider5, -80);
  lv_obj_set_y(ui_Slider5, 100);
  lv_obj_set_align(ui_Slider5, LV_ALIGN_TOP_MID);
  lv_obj_t *ui_Label11 = lv_label_create(ui_Slider5);
  lv_label_set_text(ui_Label11, "0%");
  lv_obj_align_to(ui_Label11, ui_Slider5, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_color(ui_Label11, lv_color_hex(0xFFFFFF),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  ui_Label12 = lv_label_create(parent);
  lv_label_set_text(ui_Label12, "时域");
  lv_obj_align_to(ui_Label12, ui_Slider5, LV_ALIGN_OUT_LEFT_MID, -3, 0);

  ui_Slider6 = lv_slider_create(parent);
  lv_obj_set_width(ui_Slider6, 50);
  lv_obj_set_height(ui_Slider6, 10);
  lv_obj_set_x(ui_Slider6, 15);
  lv_obj_set_y(ui_Slider6, 100);
  lv_obj_set_align(ui_Slider6, LV_ALIGN_TOP_MID);
  lv_obj_t *ui_Label13 = lv_label_create(ui_Slider6);
  lv_label_set_text(ui_Label13, "0%");
  lv_obj_align_to(ui_Label13, ui_Slider6, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_color(ui_Label13, lv_color_hex(0xFFFFFF),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  ui_Label14 = lv_label_create(parent);
  lv_label_set_text(ui_Label14, "空域");
  lv_obj_align_to(ui_Label14, ui_Slider6, LV_ALIGN_OUT_LEFT_MID, -3, 0);

  lv_obj_t *ui_Dropdown2 = lv_dropdown_create(parent);
  lv_dropdown_set_options(ui_Dropdown2, "关闭\n"
                                        "普通模式");
  lv_obj_set_width(ui_Dropdown2, 100);
  lv_obj_set_height(ui_Dropdown2, 30);
  lv_obj_set_x(ui_Dropdown2, -10);
  lv_obj_set_y(ui_Dropdown2, 125);
  lv_obj_set_align(ui_Dropdown2, LV_ALIGN_TOP_MID);
  lv_obj_set_style_pad_top(ui_Dropdown2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(ui_Dropdown2, 8, LV_PART_INDICATOR);
  lv_dropdown_set_symbol(ui_Dropdown2, LV_SYMBOL_DOWN);
  lv_obj_set_style_text_font(ui_Dropdown2, &ui_font_chinese_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_Dropdown2, &lv_font_montserrat_14,
                             LV_PART_INDICATOR); // 箭头使用符号字体
  lv_obj_set_style_text_font(lv_dropdown_get_list(ui_Dropdown2),
                             &ui_font_chinese_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_t *ui_Label15 = lv_label_create(parent);
  lv_label_set_text(ui_Label15, "细节增强");
  lv_obj_align_to(ui_Label15, ui_Dropdown2, LV_ALIGN_OUT_LEFT_MID, -15, 0);

  ui_Slider4 = lv_slider_create(parent);
  lv_obj_set_width(ui_Slider4, 96);
  lv_obj_set_height(ui_Slider4, 10);
  lv_obj_set_x(ui_Slider4, -10);
  lv_obj_set_y(ui_Slider4, 165);
  lv_obj_set_align(ui_Slider4, LV_ALIGN_TOP_MID);
  lv_obj_t *ui_Label8 = lv_label_create(ui_Slider4);
  lv_label_set_text(ui_Label8, "0%");
  lv_obj_align_to(ui_Label8, ui_Slider4, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_color(ui_Label8, lv_color_hex(0xFFFFFF),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_t *ui_Label9 = lv_label_create(parent);
  lv_label_set_text(ui_Label9, "增强等级");
  lv_obj_align_to(ui_Label9, ui_Slider4, LV_ALIGN_OUT_LEFT_MID, -10, 0);

  lv_obj_t *ui_Roller3 = lv_roller_create(parent);
  lv_roller_set_options(ui_Roller3,
                        "白热\n黑热\n融合1\n融合2\n彩虹\n铁红1\n铁红2\n深褐色\n"
                        "色彩1\n色彩2\n冰火\n雨\n红热\n绿热\n深蓝",
                        LV_ROLLER_MODE_INFINITE);
  lv_obj_set_width(ui_Roller3, 85);
  lv_obj_set_height(ui_Roller3, 100);
  lv_obj_set_x(ui_Roller3, 95);
  lv_obj_set_y(ui_Roller3, 25);
  lv_obj_set_align(ui_Roller3, LV_ALIGN_TOP_MID);
  lv_obj_t *ui_Label5 = lv_label_create(parent);
  lv_obj_align_to(ui_Label5, ui_Roller3, LV_ALIGN_OUT_TOP_MID, -5, -5);
  lv_label_set_text(ui_Label5, "调色板");

  lv_obj_t *ui_Button1 = lv_btn_create(parent);
  lv_obj_set_width(ui_Button1, 80);
  lv_obj_set_height(ui_Button1, 40);
  lv_obj_set_x(ui_Button1, 95);
  lv_obj_set_y(ui_Button1, 135);
  lv_obj_set_align(ui_Button1, LV_ALIGN_TOP_MID);
  lv_obj_add_flag(ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
  lv_obj_clear_flag(ui_Button1, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
  lv_obj_set_style_bg_color(ui_Button1, lv_color_hex(0xE28D00),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_t *ui_Label16 = lv_label_create(ui_Button1);
  lv_obj_set_width(ui_Label16, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label16, LV_SIZE_CONTENT); /// 1
  lv_obj_set_align(ui_Label16, LV_ALIGN_CENTER);
  lv_label_set_text(ui_Label16, "清除噪声");
  lv_obj_set_style_text_font(ui_Label16, &ui_font_chinese_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

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
  lv_obj_add_event_cb(
      ui_Slider1,
      [](lv_event_t *e) {
        int value = lv_slider_get_value(e->target);
        char buf[8];
        lv_snprintf(buf, sizeof(buf), "%d%%", value);
        lv_label_set_text(lv_obj_get_child(e->target, 0), buf);
        globalSettings.cameraBrightness = value;
      },
      LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(
      ui_Slider2,
      [](lv_event_t *e) {
        int value = lv_slider_get_value(e->target);
        char buf[8];
        lv_snprintf(buf, sizeof(buf), "%d%%", value);
        lv_label_set_text(lv_obj_get_child(e->target, 0), buf);
        globalSettings.cameraContrast = value;
      },
      LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(
      ui_Dropdown1,
      [](lv_event_t *e) {
        switch (lv_dropdown_get_selected(e->target)) {
        case 0: {
          globalSettings.enableNoiseReduce = IR_DNR_MODE_CLOSE;
          lv_obj_add_flag(ui_Label12, LV_OBJ_FLAG_HIDDEN);
          lv_obj_add_flag(ui_Slider5, LV_OBJ_FLAG_HIDDEN);
          lv_obj_add_flag(ui_Label14, LV_OBJ_FLAG_HIDDEN);
          lv_obj_add_flag(ui_Slider6, LV_OBJ_FLAG_HIDDEN);
          lv_obj_clear_flag(ui_Label7, LV_OBJ_FLAG_HIDDEN);
          lv_obj_clear_flag(ui_Slider3, LV_OBJ_FLAG_HIDDEN);
          set_disable(ui_Slider3);
          break;
        }
        case 1: {
          globalSettings.enableNoiseReduce = IR_DNR_MODE_GENERAL;
          lv_obj_add_flag(ui_Label12, LV_OBJ_FLAG_HIDDEN);
          lv_obj_add_flag(ui_Slider5, LV_OBJ_FLAG_HIDDEN);
          lv_obj_add_flag(ui_Label14, LV_OBJ_FLAG_HIDDEN);
          lv_obj_add_flag(ui_Slider6, LV_OBJ_FLAG_HIDDEN);
          lv_obj_clear_flag(ui_Label7, LV_OBJ_FLAG_HIDDEN);
          lv_obj_clear_flag(ui_Slider3, LV_OBJ_FLAG_HIDDEN);
          set_enable(ui_Slider3);
          break;
        }
        case 2: {
          globalSettings.enableNoiseReduce = IR_DNR_MODE_ADVANCED;
          lv_obj_clear_flag(ui_Label12, LV_OBJ_FLAG_HIDDEN);
          lv_obj_clear_flag(ui_Slider5, LV_OBJ_FLAG_HIDDEN);
          lv_obj_clear_flag(ui_Label14, LV_OBJ_FLAG_HIDDEN);
          lv_obj_clear_flag(ui_Slider6, LV_OBJ_FLAG_HIDDEN);
          lv_obj_add_flag(ui_Label7, LV_OBJ_FLAG_HIDDEN);
          lv_obj_add_flag(ui_Slider3, LV_OBJ_FLAG_HIDDEN);
          break;
        }
        }
      },
      LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(
      ui_Slider3,
      [](lv_event_t *e) {
        int value = lv_slider_get_value(e->target);
        char buf[8];
        lv_snprintf(buf, sizeof(buf), "%d%%", value);
        lv_label_set_text(lv_obj_get_child(e->target, 0), buf);
        globalSettings.noiseReduceLevel = value;
      },
      LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(
      ui_Slider5,
      [](lv_event_t *e) {
        int value = lv_slider_get_value(e->target);
        char buf[8];
        lv_snprintf(buf, sizeof(buf), "%d%%", value);
        lv_label_set_text(lv_obj_get_child(e->target, 0), buf);
        globalSettings.noiseReduceFrameLevel = value;
      },
      LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(
      ui_Slider6,
      [](lv_event_t *e) {
        int value = lv_slider_get_value(e->target);
        char buf[8];
        lv_snprintf(buf, sizeof(buf), "%d%%", value);
        lv_label_set_text(lv_obj_get_child(e->target, 0), buf);
        globalSettings.noiseReduceInterFrameLevel = value;
      },
      LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(
      ui_Dropdown2,
      [](lv_event_t *e) {
        switch (lv_dropdown_get_selected(e->target)) {
        case 0: {
          globalSettings.enableDetailEnhancement = false;
          set_disable(ui_Slider4);
          break;
        }
        case 1: {
          globalSettings.enableDetailEnhancement = true;
          set_enable(ui_Slider4);
          break;
        }
        }
      },
      LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(
      ui_Slider4,
      [](lv_event_t *e) {
        int value = lv_slider_get_value(e->target);
        char buf[8];
        lv_snprintf(buf, sizeof(buf), "%d%%", value);
        lv_label_set_text(lv_obj_get_child(e->target, 0), buf);
        globalSettings.detailEnhancementLevel = value;
      },
      LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(
      ui_Button1, [](lv_event_t *e) { cameraUtils.calibrateManually(); },
      LV_EVENT_CLICKED, NULL);

  // 当前设置
  char buf[8];
  lv_slider_set_value(ui_Slider1, globalSettings.cameraBrightness, LV_ANIM_OFF);
  lv_snprintf(buf, sizeof(buf), "%d%%", globalSettings.cameraBrightness);
  lv_label_set_text(lv_obj_get_child(ui_Slider1, 0), buf);
  lv_slider_set_value(ui_Slider2, globalSettings.cameraContrast, LV_ANIM_OFF);
  lv_snprintf(buf, sizeof(buf), "%d%%", globalSettings.cameraContrast);
  lv_label_set_text(lv_obj_get_child(ui_Slider2, 0), buf);
  switch (globalSettings.enableNoiseReduce) {
  case IR_DNR_MODE_CLOSE: {
    lv_dropdown_set_selected(ui_Dropdown1, 0);
    lv_obj_add_flag(ui_Label12, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_Slider5, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_Label14, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_Slider6, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_Label7, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_Slider3, LV_OBJ_FLAG_HIDDEN);
    lv_slider_set_value(ui_Slider3, globalSettings.noiseReduceLevel,
                        LV_ANIM_OFF);
    break;
  }
  case IR_DNR_MODE_GENERAL: {
    lv_dropdown_set_selected(ui_Dropdown1, 1);
    lv_obj_add_flag(ui_Label12, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_Slider5, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_Label14, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_Slider6, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_Label7, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_Slider3, LV_OBJ_FLAG_HIDDEN);
    lv_slider_set_value(ui_Slider3, globalSettings.noiseReduceLevel,
                        LV_ANIM_OFF);
    break;
  }
  case IR_DNR_MODE_ADVANCED: {
    lv_dropdown_set_selected(ui_Dropdown1, 2);
    lv_obj_clear_flag(ui_Label12, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_Slider5, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_Label14, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_Slider6, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_Label7, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_Slider3, LV_OBJ_FLAG_HIDDEN);
    break;
  }
  }
  lv_snprintf(buf, sizeof(buf), "%d%%", globalSettings.noiseReduceLevel);
  lv_label_set_text(lv_obj_get_child(ui_Slider3, 0), buf);
  set_enable(ui_Slider3);
  lv_slider_set_value(ui_Slider5, globalSettings.noiseReduceFrameLevel,
                      LV_ANIM_OFF);
  lv_snprintf(buf, sizeof(buf), "%d%%", globalSettings.noiseReduceFrameLevel);
  lv_label_set_text(lv_obj_get_child(ui_Slider5, 0), buf);
  lv_slider_set_value(ui_Slider6, globalSettings.noiseReduceInterFrameLevel,
                      LV_ANIM_OFF);
  lv_snprintf(buf, sizeof(buf), "%d%%",
              globalSettings.noiseReduceInterFrameLevel);
  lv_label_set_text(lv_obj_get_child(ui_Slider6, 0), buf);
  if (globalSettings.enableDetailEnhancement) {
    lv_dropdown_set_selected(ui_Dropdown2, 1);
    set_enable(ui_Slider4);
  } else {
    lv_dropdown_set_selected(ui_Dropdown2, 0);
    set_disable(ui_Slider4);
  }
  lv_slider_set_value(ui_Slider4, globalSettings.detailEnhancementLevel,
                      LV_ANIM_OFF);
  lv_snprintf(buf, sizeof(buf), "%d%%", globalSettings.detailEnhancementLevel);
  lv_label_set_text(lv_obj_get_child(ui_Slider4, 0), buf);
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
