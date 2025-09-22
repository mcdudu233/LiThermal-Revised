#include <my_main.h>

lv_obj_t *crosshairs_max_obj = NULL;
lv_obj_t *crosshairs_min_obj = NULL;
lv_obj_t *crosshairs_center_obj = NULL;
lv_obj_t *crosshairs_max = NULL;
lv_obj_t *crosshairs_min = NULL;
lv_obj_t *crosshairs_center = NULL;
lv_obj_t *crosshairs_label_max = NULL;
lv_obj_t *crosshairs_label_min = NULL;
lv_obj_t *crosshairs_label_center = NULL;

extern "C" const lv_img_dsc_t crosshairs;
void ui_crosshairs_updateVisibility()
{
    if (globalSettings.use4117Cursors) {
        lv_obj_add_flag(crosshairs_max_obj, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(crosshairs_min_obj, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(crosshairs_center_obj, LV_OBJ_FLAG_HIDDEN);
        return;
    }
    if (globalSettings.enableMaxValueDisplay)
    {
        lv_obj_clear_flag(crosshairs_max_obj, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_add_flag(crosshairs_max_obj, LV_OBJ_FLAG_HIDDEN);
    }
    if (globalSettings.enableMinValueDisplay)
    {
        lv_obj_clear_flag(crosshairs_min_obj, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_add_flag(crosshairs_min_obj, LV_OBJ_FLAG_HIDDEN);
    }
    if (globalSettings.enableCenterValueDisplay)
    {
        lv_obj_clear_flag(crosshairs_center_obj, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_add_flag(crosshairs_center_obj, LV_OBJ_FLAG_HIDDEN);
    }
    lv_obj_move_foreground(crosshairs_max_obj);
    lv_obj_move_foreground(crosshairs_min_obj);
    lv_obj_move_foreground(crosshairs_center_obj);
}

static void crosshair_anim_move(lv_obj_t *obj, lv_coord_t x, lv_coord_t y)
{
    lv_anim_t a;
    int16_t p;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_path_cb(&a, lv_anim_path_linear);
    lv_anim_set_time(&a, 40);
    lv_anim_set_delay(&a, 0);
    p = lv_obj_get_style_x(obj, 0);
    if (p != x)
    {
        lv_anim_set_values(&a, p, x);
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
        lv_anim_start(&a);
    }
    p = lv_obj_get_style_y(obj, 0);
    if (p != y)
    {
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
        lv_anim_set_values(&a, p, y);
        lv_anim_start(&a);
    }
}
static bool hidden_by_view = false;
void ui_crosshairs_updatePos()
{
    float x, y;
    char buffer[16];
    if (globalSettings.use4117Cursors)
    {
        return;
    }
    if (hidden_by_view == true)
    {
        if (current_mode == MODE_MAINPAGE || current_mode == MODE_CAMERA_SETTINGS)
        {
            hidden_by_view = false;
            ui_crosshairs_updateVisibility();
        }
        else
        {
            return;
        }
    }
    if (hidden_by_view == false && current_mode != MODE_MAINPAGE && current_mode != MODE_CAMERA_SETTINGS)
    {
        hidden_by_view = true;
        lv_obj_add_flag(crosshairs_max_obj, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(crosshairs_min_obj, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(crosshairs_center_obj, LV_OBJ_FLAG_HIDDEN);
    }
    if (globalSettings.enableMaxValueDisplay)
    {
        x = cameraUtils.lastResult.MaxTemperaturePoint.positionX;
        x = x * 320;
        y = cameraUtils.lastResult.MaxTemperaturePoint.positionY;
        y = y * 240;
        x -= 7;
        y -= 7;
        crosshair_anim_move(crosshairs_max_obj, x, y);
        sprintf(buffer, "%.1f", cameraUtils.lastResult.maxTemperature);
        lv_label_set_text(crosshairs_label_max, buffer);
    }
    if (globalSettings.enableMinValueDisplay)
    {
        x = cameraUtils.lastResult.MinTemperaturePoint.positionX;
        x = x * 320;
        y = cameraUtils.lastResult.MinTemperaturePoint.positionY;
        y = y * 240;
        x -= 7;
        y -= 7;
        crosshair_anim_move(crosshairs_min_obj, x, y);
        sprintf(buffer, "%.1f", cameraUtils.lastResult.minTemperature);
        lv_label_set_text(crosshairs_label_min, buffer);
    }
    if (globalSettings.enableCenterValueDisplay)
    {
        x = 160;
        y = 120;
        x -= 7;
        y -= 7;
        crosshair_anim_move(crosshairs_center_obj, x, y);
        sprintf(buffer, "%.1f", cameraUtils.lastResult.centerTemperature);
        lv_label_set_text(crosshairs_label_center, buffer);
    }
}

void ui_crosshairs_create()
{
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
    lv_obj_set_style_text_color(crosshairs_label_max, lv_color_make(0xEC, 0x8E, 0x9C));
    lv_obj_set_style_bg_color(crosshairs_label_max, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(crosshairs_label_max, LV_OPA_50, 0);
    lv_obj_set_style_radius(crosshairs_label_max, 3, 0);
    lv_obj_align_to(crosshairs_label_max, crosshairs_max, LV_ALIGN_OUT_RIGHT_MID, 0, 0);

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
    lv_obj_set_style_text_color(crosshairs_label_min, lv_color_make(0x87, 0xCE, 0xEB));
    lv_obj_set_style_bg_color(crosshairs_label_min, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(crosshairs_label_min, LV_OPA_50, 0);
    lv_obj_set_style_radius(crosshairs_label_min, 3, 0);
    lv_obj_align_to(crosshairs_label_min, crosshairs_min, LV_ALIGN_OUT_RIGHT_MID, 0, 0);

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
    lv_obj_set_style_text_font(crosshairs_label_center, &lv_font_montserrat_12, 0);
    lv_obj_set_style_bg_color(crosshairs_label_center, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(crosshairs_label_center, LV_OPA_30, 0);
    lv_obj_set_style_radius(crosshairs_label_center, 3, 0);
    lv_obj_align_to(crosshairs_label_center, crosshairs_center, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    if (globalSettings.use4117Cursors)
    {
        lv_obj_add_flag(crosshairs_max_obj, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(crosshairs_min_obj, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(crosshairs_center_obj, LV_OBJ_FLAG_HIDDEN);
    }
}
