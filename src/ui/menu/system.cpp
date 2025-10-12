#include "ui/menu/system.h"

static MyCard mycardMenuSystem;
static int factory_reset_cnt;
static lv_obj_t *ui_list_picture_format;
static lv_obj_t *ui_list_video_format;
static lv_obj_t *ui_switch_save_osd;
static lv_obj_t *ui_switch_buildin_cursor;
static lv_obj_t *ui_switch_display_battery;

static void menu_system_construct(lv_obj_t *parent) {
  factory_reset_cnt = 3;
  // ui_Panel2 = lv_obj_create(ui_Screen4);
  // lv_obj_set_width(ui_Panel2, 300);
  // lv_obj_set_height(ui_Panel2, 220);
  // lv_obj_set_x(ui_Panel2, 0);
  // lv_obj_set_y(ui_Panel2, 30);
  // lv_obj_set_align(ui_Panel2, LV_ALIGN_TOP_MID);
  lv_obj_clear_flag(parent, LV_OBJ_FLAG_SCROLLABLE); /// Flags
  lv_obj_set_style_text_font(parent, &ui_font_chinese_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Panel11 = lv_obj_create(parent);
  lv_obj_set_style_pad_all(ui_Panel11, 0, 0);
  lv_obj_set_width(ui_Panel11, 130);
  lv_obj_set_height(ui_Panel11, 40);
  lv_obj_set_x(ui_Panel11, 0);
  lv_obj_set_y(ui_Panel11, -10);
  lv_obj_set_style_border_width(ui_Panel11, LV_STATE_DEFAULT, 0);
  lv_obj_clear_flag(ui_Panel11, LV_OBJ_FLAG_SCROLLABLE); /// Flags

  lv_obj_t *ui_Label17 = lv_label_create(ui_Panel11);
  lv_obj_set_width(ui_Label17, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label17, LV_SIZE_CONTENT); /// 1
  lv_obj_align(ui_Label17, LV_ALIGN_LEFT_MID, 0, 0);
  lv_label_set_text(ui_Label17, "内置准星");
  lv_obj_set_style_text_font(ui_Label17, &ui_font_chinese_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_switch_buildin_cursor = lv_switch_create(ui_Panel11);
  lv_obj_set_width(ui_switch_buildin_cursor, 50);
  lv_obj_set_height(ui_switch_buildin_cursor, 25);
  lv_obj_align(ui_switch_buildin_cursor, LV_ALIGN_RIGHT_MID, -6, 0);
  lv_obj_add_flag(ui_switch_buildin_cursor, LV_OBJ_FLAG_EVENT_BUBBLE);

  lv_obj_t *ui_Panel5 = lv_obj_create(parent);
  lv_obj_set_style_pad_all(ui_Panel5, 0, 0);
  lv_obj_set_width(ui_Panel5, 135);
  lv_obj_set_height(ui_Panel5, 40);
  lv_obj_set_x(ui_Panel5, 140);
  lv_obj_set_y(ui_Panel5, -10);
  lv_obj_set_style_border_width(ui_Panel5, LV_STATE_DEFAULT, 0);
  lv_obj_clear_flag(ui_Panel5, LV_OBJ_FLAG_SCROLLABLE); /// Flags

  lv_obj_t *ui_Label18 = lv_label_create(ui_Panel5);
  lv_obj_set_width(ui_Label18, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label18, LV_SIZE_CONTENT); /// 1
  lv_obj_align(ui_Label18, LV_ALIGN_LEFT_MID, 0, 0);
  lv_label_set_text(ui_Label18, "录制OSD");
  lv_obj_set_style_text_font(ui_Label18, &ui_font_chinese_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_switch_save_osd = lv_switch_create(ui_Panel5);
  lv_obj_set_width(ui_switch_save_osd, 50);
  lv_obj_set_height(ui_switch_save_osd, 25);
  lv_obj_align(ui_switch_save_osd, LV_ALIGN_RIGHT_MID, -6, 0);
  lv_obj_add_flag(ui_switch_save_osd, LV_OBJ_FLAG_EVENT_BUBBLE);

  lv_obj_t *ui_Panel19 = lv_obj_create(parent);
  lv_obj_set_style_pad_all(ui_Panel19, 0, 0);
  lv_obj_set_width(ui_Panel19, 275);
  lv_obj_set_height(ui_Panel19, 38);
  lv_obj_set_x(ui_Panel19, 0);
  lv_obj_set_y(ui_Panel19, 26);
  lv_obj_set_style_border_width(ui_Panel19, LV_STATE_DEFAULT, 0);
  lv_obj_clear_flag(ui_Panel19, LV_OBJ_FLAG_SCROLLABLE); /// Flags

  lv_obj_t *ui_Label20 = lv_label_create(ui_Panel19);
  lv_obj_set_width(ui_Label20, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label20, LV_SIZE_CONTENT); /// 1
  lv_obj_align(ui_Label20, LV_ALIGN_LEFT_MID, 0, 0);
  lv_label_set_text(ui_Label20, "始终在主界面显示剩余电量");
  lv_obj_set_style_text_font(ui_Label20, &ui_font_chinese_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_switch_display_battery = lv_switch_create(ui_Panel19);
  lv_obj_set_width(ui_switch_display_battery, 50);
  lv_obj_set_height(ui_switch_display_battery, 25);
  lv_obj_align(ui_switch_display_battery, LV_ALIGN_RIGHT_MID, -6, 0);
  lv_obj_add_flag(ui_switch_display_battery, LV_OBJ_FLAG_EVENT_BUBBLE);

  lv_obj_t *ui_Panel10 = lv_obj_create(parent);
  lv_obj_set_style_pad_all(ui_Panel10, 0, 0);
  lv_obj_set_width(ui_Panel10, 130);
  lv_obj_set_height(ui_Panel10, 42);
  lv_obj_set_x(ui_Panel10, 0);
  lv_obj_set_y(ui_Panel10, 65);
  lv_obj_set_style_border_width(ui_Panel10, LV_STATE_DEFAULT, 0);
  lv_obj_clear_flag(ui_Panel10, LV_OBJ_FLAG_SCROLLABLE); /// Flags

  lv_obj_t *ui_Label14 = lv_label_create(ui_Panel10);
  lv_obj_set_width(ui_Label14, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label14, LV_SIZE_CONTENT); /// 1
  lv_obj_align(ui_Label14, LV_ALIGN_LEFT_MID, 0, 0);
  lv_label_set_text(ui_Label14, "图片");
  lv_obj_set_style_text_font(ui_Label14, &ui_font_chinese_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_list_picture_format = lv_dropdown_create(ui_Panel10);
  lv_dropdown_set_options(ui_list_picture_format, "JPEG\n"
                                                  "RAW\n"
                                                  "JPG+RAW");
  lv_obj_set_width(ui_list_picture_format, 90);
  lv_obj_set_height(ui_list_picture_format, 35);
  lv_obj_align(ui_list_picture_format, LV_ALIGN_RIGHT_MID, -3, 0);
  lv_obj_set_style_text_font(ui_list_picture_format, &lv_font_montserrat_12,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Panel12 = lv_obj_create(parent);
  lv_obj_set_style_pad_all(ui_Panel12, 0, 0);
  lv_obj_set_width(ui_Panel12, 130);
  lv_obj_set_height(ui_Panel12, 42);
  lv_obj_set_x(ui_Panel12, 140);
  lv_obj_set_y(ui_Panel12, 65);
  lv_obj_set_style_border_width(ui_Panel12, LV_STATE_DEFAULT, 0);
  lv_obj_clear_flag(ui_Panel12, LV_OBJ_FLAG_SCROLLABLE); /// Flags

  lv_obj_t *ui_Label16 = lv_label_create(ui_Panel12);
  lv_obj_set_width(ui_Label16, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label16, LV_SIZE_CONTENT); /// 1
  lv_obj_align(ui_Label16, LV_ALIGN_LEFT_MID, 0, 0);
  lv_label_set_text(ui_Label16, "视频");
  lv_obj_set_style_text_font(ui_Label16, &ui_font_chinese_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_list_video_format = lv_dropdown_create(ui_Panel12);
  lv_dropdown_set_options(ui_list_video_format, "MP4\n"
                                                "MJPEG\n"
                                                "MP4+MJPG");
  lv_obj_set_width(ui_list_video_format, 90);
  lv_obj_set_height(ui_list_video_format, 35);
  lv_obj_align(ui_list_video_format, LV_ALIGN_RIGHT_MID, -3, 0);
  lv_obj_set_style_text_font(ui_list_video_format, &lv_font_montserrat_12,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  //  lv_obj_t *ui_Button1 = lv_btn_create(parent);
  //  lv_obj_set_width(ui_Button1, 140);
  //  lv_obj_set_height(ui_Button1, 40);
  //  lv_obj_set_x(ui_Button1, 0);
  //  lv_obj_set_y(ui_Button1, 100);
  //  lv_obj_add_flag(ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
  //  lv_obj_clear_flag(ui_Button1, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
  //  lv_obj_set_style_bg_color(ui_Button1, lv_color_hex(0xE28D00),
  //                            LV_PART_MAIN | LV_STATE_DEFAULT);
  //  lv_obj_set_style_bg_opa(ui_Button1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  //
  //  lv_obj_t *ui_Label12 = lv_label_create(ui_Button1);
  //  lv_obj_set_width(ui_Label12, LV_SIZE_CONTENT);  /// 1
  //  lv_obj_set_height(ui_Label12, LV_SIZE_CONTENT); /// 1
  //  lv_obj_set_align(ui_Label12, LV_ALIGN_CENTER);
  //  lv_label_set_text(ui_Label12, "手动清除噪声");
  //  lv_obj_set_style_text_font(ui_Label12, &ui_font_chinese_16,
  //                             LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_button_default = lv_btn_create(parent);
  lv_obj_set_width(ui_button_default, 120);
  lv_obj_set_height(ui_button_default, 40);
  lv_obj_set_x(ui_button_default, 0);
  lv_obj_set_y(ui_button_default, 115);
  lv_obj_add_flag(ui_button_default, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
  lv_obj_clear_flag(ui_button_default, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
  lv_obj_set_style_bg_color(ui_button_default, lv_color_hex(0xF44336),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_button_default, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Label13 = lv_label_create(ui_button_default);
  lv_obj_set_width(ui_Label13, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label13, LV_SIZE_CONTENT); /// 1
  lv_obj_set_align(ui_Label13, LV_ALIGN_CENTER);
  lv_label_set_text(ui_Label13, "恢复默认设置");
  lv_obj_set_style_text_font(ui_Label13, &ui_font_chinese_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_button_shutdown = lv_btn_create(parent);
  lv_obj_set_width(ui_button_shutdown, 70);
  lv_obj_set_height(ui_button_shutdown, 40);
  lv_obj_set_x(ui_button_shutdown, 125);
  lv_obj_set_y(ui_button_shutdown, 115);
  lv_obj_add_flag(ui_button_shutdown, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
  lv_obj_clear_flag(ui_button_shutdown, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
  lv_obj_set_style_bg_color(ui_button_shutdown, lv_color_hex(0x238A22),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_button_shutdown, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Label19 = lv_label_create(ui_button_shutdown);
  lv_obj_set_width(ui_Label19, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label19, LV_SIZE_CONTENT); /// 1
  lv_obj_set_align(ui_Label19, LV_ALIGN_CENTER);
  lv_label_set_text(ui_Label19, "关机");
  lv_obj_set_style_text_font(ui_Label19, &ui_font_chinese_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_button_restart = lv_btn_create(parent);
  lv_obj_set_width(ui_button_restart, 70);
  lv_obj_set_height(ui_button_restart, 40);
  lv_obj_set_x(ui_button_restart, 200);
  lv_obj_set_y(ui_button_restart, 115);
  lv_obj_add_flag(ui_button_restart, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
  lv_obj_clear_flag(ui_button_restart, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
  lv_obj_set_style_bg_color(ui_button_restart, lv_color_hex(0xE28D00),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_button_restart, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Label12 = lv_label_create(ui_button_restart);
  lv_obj_set_width(ui_Label12, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label12, LV_SIZE_CONTENT); /// 1
  lv_obj_set_align(ui_Label12, LV_ALIGN_CENTER);
  lv_label_set_text(ui_Label12, "重启");
  lv_obj_set_style_text_font(ui_Label12, &ui_font_chinese_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Label15 = lv_label_create(parent);
  lv_obj_set_width(ui_Label15, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label15, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_Label15, 0);
  lv_obj_set_y(ui_Label15, 160);
  lv_obj_set_align(ui_Label15, LV_ALIGN_TOP_MID);
  lv_label_set_text(
      ui_Label15,
      "作者：小李电子实验室(原)、mcdudu233(修订)\n开源协议：GPL3.0");
  lv_obj_set_style_text_color(ui_Label15, lv_color_hex(0x808080),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui_Label15, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(ui_Label15, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_Label15, &ui_font_chinese_14,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  //  lv_group_focus_obj(ui_Button1);

  lv_obj_add_event_cb(
      ui_switch_save_osd,
      [](lv_event_t *e) {
        globalSettings.preserveOSD =
            lv_obj_has_state(e->target, LV_STATE_CHECKED);
      },
      LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(
      ui_switch_buildin_cursor,
      [](lv_event_t *e) {
        globalSettings.useBuildinCursors =
            lv_obj_has_state(e->target, LV_STATE_CHECKED);
      },
      LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(
      ui_switch_display_battery,
      [](lv_event_t *e) {
        globalSettings.displayBattery =
            lv_obj_has_state(e->target, LV_STATE_CHECKED);
      },
      LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(
      ui_list_picture_format,
      [](lv_event_t *e) {
        switch (lv_dropdown_get_selected(e->target)) {
        case 0: {
          globalSettings.pictureFormat = jpeg;
          break;
        }
        case 1: {
          globalSettings.pictureFormat = raw;
          break;
        }
        case 2: {
          globalSettings.pictureFormat = jpeg_raw;
          break;
        }
        }
      },
      LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(
      ui_list_video_format,
      [](lv_event_t *e) {
        switch (lv_dropdown_get_selected(e->target)) {
        case 0: {
          globalSettings.videoFormat = mp4;
          break;
        }
        case 1: {
          globalSettings.videoFormat = mjpeg;
          break;
        }
        case 2: {
          globalSettings.videoFormat = mp4_mjpeg;
          break;
        }
        }
      },
      LV_EVENT_VALUE_CHANGED, NULL);
  //  lv_obj_add_event_cb(
  //      ui_Button1, [](lv_event_t *e) { cameraUtils.calibrateManually(); },
  //      LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(
      ui_button_default,
      [](lv_event_t *e) {
        if (factory_reset_cnt == 0) {
          factory_reset_cnt = 4;
          lv_label_set_text(lv_obj_get_child(e->target, 0), "已恢复");
          settings_default();
          settings_save();
          lv_obj_clear_state(ui_switch_save_osd, LV_STATE_CHECKED);
          lv_obj_clear_state(ui_switch_buildin_cursor, LV_STATE_CHECKED);
          lv_obj_add_state(ui_switch_display_battery, LV_STATE_CHECKED);
          lv_dropdown_set_selected(ui_list_picture_format, 2);
          lv_dropdown_set_selected(ui_list_video_format, 2);
        } else {
          lv_label_set_text_fmt(lv_obj_get_child(e->target, 0),
                                "再按%d次后恢复", factory_reset_cnt);
        }
        --factory_reset_cnt;
      },
      LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(
      ui_button_shutdown,
      [](lv_event_t *e) {
        lv_label_set_text(lv_obj_get_child(e->target, 0), "关机中");
        printf("Poweroff!\n");
        settings_save();
        global_poweroff_request = true;
      },
      LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(
      ui_button_restart,
      [](lv_event_t *e) {
        lv_label_set_text(lv_obj_get_child(e->target, 0), "重启中");
        printf("Restart!\n");
        settings_save();
        exit(-1);
      },
      LV_EVENT_CLICKED, NULL);

  if (globalSettings.preserveOSD)
    lv_obj_add_state(ui_switch_save_osd, LV_STATE_CHECKED);
  if (globalSettings.useBuildinCursors)
    lv_obj_add_state(ui_switch_buildin_cursor, LV_STATE_CHECKED);
  if (globalSettings.displayBattery)
    lv_obj_add_state(ui_switch_display_battery, LV_STATE_CHECKED);
  switch (globalSettings.pictureFormat) {
  case jpeg: {
    lv_dropdown_set_selected(ui_list_picture_format, 0);
    break;
  }
  case raw: {
    lv_dropdown_set_selected(ui_list_picture_format, 1);
    break;
  }
  case jpeg_raw: {
    lv_dropdown_set_selected(ui_list_picture_format, 2);
    break;
  }
  }
  switch (globalSettings.videoFormat) {
  case mp4: {
    lv_dropdown_set_selected(ui_list_video_format, 0);
    break;
  }
  case mjpeg: {
    lv_dropdown_set_selected(ui_list_video_format, 1);
    break;
  }
  case mp4_mjpeg: {
    lv_dropdown_set_selected(ui_list_video_format, 2);
    break;
  }
  }
}

void menu_system_show() {
  mycardMenuSystem.create(lv_layer_top(), 0, MENU_SYSTEM_CARD_POS_Y,
                          MENU_SYSTEM_CARD_WIDTH, MENU_SYSTEM_CARD_HEIGHT,
                          LV_ALIGN_TOP_MID);
  lv_obj_set_style_pad_all(mycardMenuSystem.obj, 15, 0);
  menu_system_construct(mycardMenuSystem.obj);
  lv_group_focus_obj(lv_obj_get_child(mycardMenuSystem.obj, 0));
  mycardMenuSystem.show(CARD_ANIM_FLY_UP);
}

void menu_system_hide() {
  mycardMenuSystem.del(CARD_ANIM_FLY_DOWN);
  settings_save();
}
