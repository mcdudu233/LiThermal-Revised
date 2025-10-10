#include "ui/brightness.h"

// 主界面滚动滚轮为调节亮度
// 跳过lvgl焦点策略，直接在hal线程调节，并弹出亮度条实时反馈
static lv_obj_t *ui_brightnessSlider = NULL;

static int current_backlight = 170;
static int last_backlight = -1;
static time_t last_tick = -1;

static bool expanded = false;

void brightness_show() {
  if (ui_brightnessSlider == NULL) {
    ui_brightnessSlider = lv_bar_create(lv_layer_sys());
    lv_bar_set_range(ui_brightnessSlider, 0, 255);
    lv_bar_set_value(ui_brightnessSlider, 75, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_brightnessSlider, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_brightnessSlider, 40);
    lv_obj_set_height(ui_brightnessSlider, UI_BRIGHTNESSBAR_HEIGHT_SHOW);
    lv_obj_set_x(ui_brightnessSlider, UI_BRIGHTNESSBAR_X_HIDE);
    lv_obj_set_y(ui_brightnessSlider, UI_BRIGHTNESSBAR_Y);
    lv_obj_set_align(ui_brightnessSlider, LV_ALIGN_RIGHT_MID);
    lv_obj_set_style_radius(ui_brightnessSlider, 8,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_brightnessSlider, lv_color_hex(0xFFE99A),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_brightnessSlider, 80,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_brightnessSlider, 0,
                            LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_brightnessSlider, lv_color_hex(0xFFFFFF),
                              LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_brightnessSlider, 255,
                            LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label4 = lv_label_create(ui_brightnessSlider);
    lv_obj_set_x(ui_Label4, 0);
    lv_obj_set_y(ui_Label4, -8);
    lv_obj_set_align(ui_Label4, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Label4, "");
    lv_obj_set_style_text_color(ui_Label4, lv_color_hex(0x000000),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_Label4, 200, 0);
    lv_obj_set_style_text_font(ui_Label4, &ui_font_fontawesome16,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
  }
  lv_anim_move(ui_brightnessSlider, UI_BRIGHTNESSBAR_X_SHOW,
               UI_BRIGHTNESSBAR_Y);
  lv_anim_size(ui_brightnessSlider, 40, UI_BRIGHTNESSBAR_HEIGHT_SHOW);
}

void brightness_hide() {
  lv_anim_move(ui_brightnessSlider, UI_BRIGHTNESSBAR_X_HIDE,
               UI_BRIGHTNESSBAR_Y);
  lv_anim_size(ui_brightnessSlider, 40, UI_BRIGHTNESSBAR_HEIGHT_HIDE);
}

void brightness_loop() {
  if (current_mode == MODE_MAINPAGE && last_encoder_direction != 0) {
    if (last_encoder_direction > 0) {
      if (globalSettings.brightness <= (255 - 8))
        globalSettings.brightness += 8;
      else
        globalSettings.brightness = 255;
    } else {
      if (globalSettings.brightness >= 8)
        globalSettings.brightness -= 8;
      else
        globalSettings.brightness = 0;
    }
    last_encoder_direction = 0;
  }

  if (current_backlight > globalSettings.brightness) {
    current_backlight -= 1;
    backlight_set(current_backlight);
  } else if (current_backlight < globalSettings.brightness) {
    current_backlight += 1;
    backlight_set(current_backlight);
  }

  if (last_backlight == -1) {
    // 第一次循环
    last_tick = time(NULL);
    last_backlight = current_backlight;
  }
  if (last_backlight != current_backlight) {
    if (!expanded) {
      expanded = true;
      LOCKLV();
      brightness_show();
      UNLOCKLV();
    }
    last_tick = time(NULL);
    LOCKLV();
    lv_bar_set_value(ui_brightnessSlider, current_backlight, LV_ANIM_OFF);
    UNLOCKLV();
    last_backlight = current_backlight;
  } else {
    if (expanded) {
      if (time(NULL) - last_tick >= BRIGHTNESSBAR_AUTO_HIDE_TIME) {
        expanded = false;
        LOCKLV();
        brightness_hide();
        UNLOCKLV();
      }
    }
  }
}
