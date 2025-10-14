#include "ui/crosshairs.h"

static lv_obj_t *crosshairs_max_obj = NULL;
static lv_obj_t *crosshairs_min_obj = NULL;
static lv_obj_t *crosshairs_center_obj = NULL;
static lv_obj_t *crosshairs_max = NULL;
static lv_obj_t *crosshairs_min = NULL;
static lv_obj_t *crosshairs_center = NULL;
static lv_obj_t *crosshairs_label_max = NULL;
static lv_obj_t *crosshairs_label_min = NULL;
static lv_obj_t *crosshairs_label_avg = NULL;
static lv_obj_t *crosshairs_label_center = NULL;

static void crosshair_move(lv_obj_t *obj, lv_coord_t x, lv_coord_t y) {
  lv_anim_t a;
  int16_t p;
  lv_anim_init(&a);
  lv_anim_set_var(&a, obj);
  lv_anim_set_path_cb(&a, lv_anim_path_linear);
  lv_anim_set_time(&a, 40);
  lv_anim_set_delay(&a, 0);
  p = lv_obj_get_style_x(obj, 0);
  if (p != x) {
    lv_anim_set_values(&a, p, x);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_start(&a);
  }
  p = lv_obj_get_style_y(obj, 0);
  if (p != y) {
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_values(&a, p, y);
    lv_anim_start(&a);
  }
}

static void crosshairs_update_visibility() {
  if (globalSettings.useBuildinCursors) {
    lv_obj_add_flag(crosshairs_max_obj, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(crosshairs_min_obj, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(crosshairs_center_obj, LV_OBJ_FLAG_HIDDEN);
    return;
  }
  if (globalSettings.enableMaxValueDisplay) {
    lv_obj_clear_flag(crosshairs_max_obj, LV_OBJ_FLAG_HIDDEN);
  } else {
    lv_obj_add_flag(crosshairs_max_obj, LV_OBJ_FLAG_HIDDEN);
  }
  if (globalSettings.enableMinValueDisplay) {
    lv_obj_clear_flag(crosshairs_min_obj, LV_OBJ_FLAG_HIDDEN);
  } else {
    lv_obj_add_flag(crosshairs_min_obj, LV_OBJ_FLAG_HIDDEN);
  }
  if (globalSettings.enableAvgValueDisplay) {
    lv_obj_clear_flag(crosshairs_label_avg, LV_OBJ_FLAG_HIDDEN);
  } else {
    lv_obj_add_flag(crosshairs_label_avg, LV_OBJ_FLAG_HIDDEN);
  }
  if (globalSettings.enableCenterValueDisplay) {
    lv_obj_clear_flag(crosshairs_center_obj, LV_OBJ_FLAG_HIDDEN);
  } else {
    lv_obj_add_flag(crosshairs_center_obj, LV_OBJ_FLAG_HIDDEN);
  }
  lv_obj_move_foreground(crosshairs_max_obj);
  lv_obj_move_foreground(crosshairs_min_obj);
  lv_obj_move_foreground(crosshairs_center_obj);
  lv_obj_move_foreground(crosshairs_label_avg);
}

void crosshairs_show() {
  if (crosshairs_max_obj == NULL || crosshairs_min_obj == NULL ||
      crosshairs_center_obj == NULL || crosshairs_max == NULL ||
      crosshairs_min == NULL || crosshairs_center == NULL ||
      crosshairs_label_max == NULL || crosshairs_label_min == NULL ||
      crosshairs_label_center == NULL || crosshairs_label_avg == NULL) {
    crosshairs_max_obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(crosshairs_max_obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(crosshairs_max_obj, 0, 0);
    lv_obj_set_style_bg_opa(crosshairs_max_obj, 0, 0);
    lv_obj_set_style_border_width(crosshairs_max_obj, 0, 0);
    lv_obj_set_style_radius(crosshairs_max_obj, 0, 0);
    lv_obj_add_flag(crosshairs_max_obj, LV_OBJ_FLAG_HIDDEN);

    crosshairs_max = lv_img_create(crosshairs_max_obj);
    lv_img_set_src(crosshairs_max, &crosshairs);
    crosshairs_label_max = lv_label_create(crosshairs_max_obj);
    lv_obj_set_style_text_font(crosshairs_label_max, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(crosshairs_label_max,
                                lv_color_make(0xFF, 0x00, 0x00), 0);
    lv_obj_set_style_bg_color(crosshairs_label_max, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(crosshairs_label_max, LV_OPA_50, 0);
    lv_obj_set_style_radius(crosshairs_label_max, 3, 0);
    lv_obj_align_to(crosshairs_label_max, crosshairs_max,
                    LV_ALIGN_OUT_RIGHT_MID, 0, 0);

    crosshairs_min_obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(crosshairs_min_obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(crosshairs_min_obj, 0, 0);
    lv_obj_set_style_bg_opa(crosshairs_min_obj, 0, 0);
    lv_obj_set_style_border_width(crosshairs_min_obj, 0, 0);
    lv_obj_set_style_radius(crosshairs_min_obj, 0, 0);
    lv_obj_add_flag(crosshairs_min_obj, LV_OBJ_FLAG_HIDDEN);

    crosshairs_min = lv_img_create(crosshairs_min_obj);
    lv_img_set_src(crosshairs_min, &crosshairs);
    crosshairs_label_min = lv_label_create(crosshairs_min_obj);
    lv_obj_set_style_text_font(crosshairs_label_min, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(crosshairs_label_min,
                                lv_color_make(0x00, 0x00, 0xFF), 0);
    lv_obj_set_style_bg_color(crosshairs_label_min, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(crosshairs_label_min, LV_OPA_50, 0);
    lv_obj_set_style_radius(crosshairs_label_min, 3, 0);
    lv_obj_align_to(crosshairs_label_min, crosshairs_min,
                    LV_ALIGN_OUT_RIGHT_MID, 0, 0);

    crosshairs_label_avg = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(crosshairs_label_avg, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(crosshairs_label_avg,
                                lv_color_make(0x00, 0xFF, 0x00), 0);
    lv_obj_set_style_bg_color(crosshairs_label_avg, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(crosshairs_label_avg, LV_OPA_30, 0);
    lv_obj_set_style_radius(crosshairs_label_avg, 3, 0);
    lv_obj_align_to(crosshairs_label_avg, lv_scr_act(), LV_ALIGN_OUT_LEFT_TOP,
                    30, 0);

    crosshairs_center_obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(crosshairs_center_obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(crosshairs_center_obj, 0, 0);
    lv_obj_set_style_bg_opa(crosshairs_center_obj, 0, 0);
    lv_obj_set_style_border_width(crosshairs_center_obj, 0, 0);
    lv_obj_set_style_radius(crosshairs_center_obj, 0, 0);
    lv_obj_add_flag(crosshairs_center_obj, LV_OBJ_FLAG_HIDDEN);

    crosshairs_center = lv_img_create(crosshairs_center_obj);
    lv_img_set_src(crosshairs_center, &crosshairs);
    crosshairs_label_center = lv_label_create(crosshairs_center_obj);
    lv_obj_set_style_text_font(crosshairs_label_center, &lv_font_montserrat_12,
                               0);
    lv_obj_set_style_bg_color(crosshairs_label_center, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(crosshairs_label_center, LV_OPA_30, 0);
    lv_obj_set_style_radius(crosshairs_label_center, 3, 0);
    lv_obj_align_to(crosshairs_label_center, crosshairs_center,
                    LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    if (globalSettings.useBuildinCursors) {
      lv_obj_add_flag(crosshairs_max_obj, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(crosshairs_min_obj, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(crosshairs_center_obj, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(crosshairs_label_avg, LV_OBJ_FLAG_HIDDEN);
    }
  }
}

void crosshairs_loop() {
  LOCKLV();
  crosshairs_show();
  crosshairs_update_visibility();
  UNLOCKLV();
  if (globalSettings.useBuildinCursors) {
    return;
  }

  float x, y;
  char buffer[16];
  if (globalSettings.enableMaxValueDisplay) {
    x = cameraUtils.lastResult.MaxTemperaturePoint.positionX;
    x = x * 320;
    y = cameraUtils.lastResult.MaxTemperaturePoint.positionY;
    y = y * 240;
    x -= 7;
    y -= 7;
    LOCKLV();
    crosshair_move(crosshairs_max_obj, x, y);
    sprintf(buffer, "%.1f", cameraUtils.lastResult.maxTemperature);
    lv_label_set_text(crosshairs_label_max, buffer);
    UNLOCKLV();
  }
  if (globalSettings.enableMinValueDisplay) {
    x = cameraUtils.lastResult.MinTemperaturePoint.positionX;
    x = x * 320;
    y = cameraUtils.lastResult.MinTemperaturePoint.positionY;
    y = y * 240;
    x -= 7;
    y -= 7;
    LOCKLV();
    crosshair_move(crosshairs_min_obj, x, y);
    sprintf(buffer, "%.1f", cameraUtils.lastResult.minTemperature);
    lv_label_set_text(crosshairs_label_min, buffer);
    UNLOCKLV();
  }
  if (globalSettings.enableAvgValueDisplay) {
    LOCKLV();
    sprintf(buffer, "%.1f", cameraUtils.lastResult.averageTemperature);
    lv_label_set_text(crosshairs_label_avg, buffer);
    UNLOCKLV();
  }
  if (globalSettings.enableCenterValueDisplay) {
    x = 160;
    y = 120;
    x -= 7;
    y -= 7;
    LOCKLV();
    crosshair_move(crosshairs_center_obj, x, y);
    sprintf(buffer, "%.1f", cameraUtils.lastResult.centerTemperature);
    lv_label_set_text(crosshairs_label_center, buffer);
    UNLOCKLV();
  }
}