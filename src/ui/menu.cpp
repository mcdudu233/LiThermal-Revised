#include "ui/menu.h"

static MyCard card_menuPage;
static bool close_for_opening_submenu = false;
static button_mode_t selected_menu_number = BUTTON_DEFAULT;
static bool expanded = false;

static void event_button_clicked_cb(lv_event_t *e) {
  lv_obj_t *target = lv_event_get_target(e);
  int code = e->code;
  switch (code) {
  case LV_EVENT_CLICKED:
    selected_menu_number =
        static_cast<button_mode_t>(reinterpret_cast<int>(e->user_data));
    close_for_opening_submenu = true;
    break;
  case LV_EVENT_FOCUSED:
    if (expanded)
      lv_anim_size(target, MENU_BUTTON_WIDTH_FOCUSED,
                   MENU_BUTTON_HEIGHT_FOCUSED, 500, 0);
    break;
  case LV_EVENT_DEFOCUSED:
    if (expanded)
      lv_anim_size(target, MENU_BUTTON_WIDTH_DEFAULT,
                   MENU_BUTTON_HEIGHT_DEFAULT, 500, 0);
    break;
  default:
    break;
  }
}

static void menu_construct(lv_obj_t *parent) {
  lv_obj_set_align(parent, LV_ALIGN_TOP_MID);
  lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(parent, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_END,
                        LV_FLEX_ALIGN_END);
  lv_obj_clear_flag(parent, LV_OBJ_FLAG_SCROLLABLE); /// Flags
  lv_obj_set_style_bg_opa(parent, 160, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(parent, 0, 0);

  lv_obj_t *ui_Button2 = lv_btn_create(parent);
  lv_obj_set_width(ui_Button2, MENU_BUTTON_WIDTH_DEFAULT);
  lv_obj_set_height(ui_Button2, MENU_BUTTON_HEIGHT_DEFAULT);
  lv_obj_set_align(ui_Button2, LV_ALIGN_TOP_MID);
  lv_obj_add_flag(ui_Button2, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
  lv_obj_clear_flag(ui_Button2, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
  lv_obj_set_style_bg_color(ui_Button2, lv_color_hex(0x282B30),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui_Button2, lv_color_hex(0x0081B3),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_bg_opa(ui_Button2, 255, LV_PART_MAIN | LV_STATE_FOCUSED);

  lv_obj_t *ui_Label4 = lv_label_create(ui_Button2);
  lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT); /// 1
  lv_obj_set_align(ui_Label4, LV_ALIGN_TOP_MID);
  lv_label_set_text(ui_Label4, "");
  lv_obj_set_style_text_font(ui_Label4, &ui_font_fontawesome24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Label5 = lv_label_create(ui_Button2);
  lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_Label5, 0);
  lv_obj_set_y(ui_Label5, 40);
  lv_obj_set_align(ui_Label5, LV_ALIGN_TOP_MID);
  lv_label_set_text(ui_Label5, "相册");
  lv_obj_set_style_text_font(ui_Label5, &ui_font_chinese_18,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Button3 = lv_btn_create(parent);
  lv_obj_set_width(ui_Button3, MENU_BUTTON_WIDTH_DEFAULT);
  lv_obj_set_height(ui_Button3, MENU_BUTTON_HEIGHT_DEFAULT);
  lv_obj_set_align(ui_Button3, LV_ALIGN_TOP_MID);
  lv_obj_add_flag(ui_Button3, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
  lv_obj_clear_flag(ui_Button3, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
  lv_obj_set_style_bg_color(ui_Button3, lv_color_hex(0x282B30),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui_Button3, lv_color_hex(0xBB9100),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_bg_opa(ui_Button3, 255, LV_PART_MAIN | LV_STATE_FOCUSED);

  lv_obj_t *ui_Label6 = lv_label_create(ui_Button3);
  lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT); /// 1
  lv_obj_set_align(ui_Label6, LV_ALIGN_TOP_MID);
  lv_label_set_text(ui_Label6, "\uE163");
  lv_obj_set_style_text_font(ui_Label6, &ui_font_fontawesome24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Label7 = lv_label_create(ui_Button3);
  lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_Label7, 0);
  lv_obj_set_y(ui_Label7, 40);
  lv_obj_set_align(ui_Label7, LV_ALIGN_TOP_MID);
  lv_label_set_text(ui_Label7, "OSD\n设置");
  lv_obj_set_style_text_font(ui_Label7, &ui_font_chinese_18,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Button5 = lv_btn_create(parent);
  lv_obj_set_width(ui_Button5, MENU_BUTTON_WIDTH_DEFAULT);
  lv_obj_set_height(ui_Button5, MENU_BUTTON_HEIGHT_DEFAULT);
  lv_obj_set_align(ui_Button5, LV_ALIGN_TOP_MID);
  lv_obj_add_flag(ui_Button5, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
  lv_obj_clear_flag(ui_Button5, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
  lv_obj_set_style_bg_color(ui_Button5, lv_color_hex(0x282B30),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui_Button5, lv_color_hex(0x008C7B),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_bg_opa(ui_Button5, 255, LV_PART_MAIN | LV_STATE_FOCUSED);

  lv_obj_t *ui_Label10 = lv_label_create(ui_Button5);
  lv_obj_set_width(ui_Label10, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label10, LV_SIZE_CONTENT); /// 1
  lv_obj_set_align(ui_Label10, LV_ALIGN_TOP_MID);
  lv_label_set_text(ui_Label10, "");
  lv_obj_set_style_text_font(ui_Label10, &ui_font_fontawesome24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Label11 = lv_label_create(ui_Button5);
  lv_obj_set_width(ui_Label11, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label11, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_Label11, 0);
  lv_obj_set_y(ui_Label11, 40);
  lv_obj_set_align(ui_Label11, LV_ALIGN_TOP_MID);
  lv_label_set_text(ui_Label11, "相机\n设置");
  lv_obj_set_style_text_font(ui_Label11, &ui_font_chinese_18,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Button4 = lv_btn_create(parent);
  lv_obj_set_width(ui_Button4, MENU_BUTTON_WIDTH_DEFAULT);
  lv_obj_set_height(ui_Button4, MENU_BUTTON_HEIGHT_DEFAULT);
  lv_obj_set_align(ui_Button4, LV_ALIGN_TOP_MID);
  lv_obj_add_flag(ui_Button4, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
  lv_obj_clear_flag(ui_Button4, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
  lv_obj_set_style_bg_color(ui_Button4, lv_color_hex(0x282B30),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui_Button4, lv_color_hex(0x960000),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_bg_opa(ui_Button4, 255, LV_PART_MAIN | LV_STATE_FOCUSED);

  lv_obj_t *ui_Label8 = lv_label_create(ui_Button4);
  lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT); /// 1
  lv_obj_set_align(ui_Label8, LV_ALIGN_TOP_MID);
  lv_label_set_text(ui_Label8, "");
  lv_obj_set_style_text_font(ui_Label8, &ui_font_fontawesome24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Label9 = lv_label_create(ui_Button4);
  lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_Label9, 0);
  lv_obj_set_y(ui_Label9, 40);
  lv_obj_set_align(ui_Label9, LV_ALIGN_TOP_MID);
  lv_label_set_text(ui_Label9, "系统\n设置");
  lv_obj_set_style_text_font(ui_Label9, &ui_font_chinese_18,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  // events
  lv_obj_add_event_cb(ui_Button2, event_button_clicked_cb, LV_EVENT_ALL,
                      reinterpret_cast<void *>((int)BUTTON_GALLERY));
  lv_obj_add_event_cb(ui_Button3, event_button_clicked_cb, LV_EVENT_ALL,
                      reinterpret_cast<void *>((int)BUTTON_OSD));
  lv_obj_add_event_cb(ui_Button5, event_button_clicked_cb, LV_EVENT_ALL,
                      reinterpret_cast<void *>((int)BUTTON_CAMERA));
  lv_obj_add_event_cb(ui_Button4, event_button_clicked_cb, LV_EVENT_ALL,
                      reinterpret_cast<void *>((int)BUTTON_SYSTEM));
}

void menu_show() {
  if (card_menuPage.obj == NULL || !lv_obj_is_valid(card_menuPage.obj)) {
    card_menuPage.create(lv_layer_sys(), -50, 0, 0, 0, LV_ALIGN_TOP_MID);
    card_menuPage.show(CARD_ANIM_NONE);
    menu_construct(card_menuPage.obj);
    lv_group_focus_obj(lv_obj_get_child(card_menuPage.obj, 0));
  }
  lv_anim_size(card_menuPage.obj, MENU_BOX_WIDTH, MENU_BOX_HEIGHT, 500, 0);
  lv_anim_move(card_menuPage.obj, 0, MENU_BOX_Y_SHOW, 500, 0);
}

void menu_hide() {
  lv_anim_size(card_menuPage.obj, 0, 0, 500, 0);
  lv_anim_move(card_menuPage.obj, -50, 0, 500, 0);
}

void menu_loop() {
  if (!expanded) {
    if (HAL::key_press_event[1]) {
      HAL::key_press_event[1] = false;
      switch (current_mode) {
      case MODE_MAIN:
        expanded = true;
        close_for_opening_submenu = false;
        LOCKLV();
        menu_show();
        current_mode = MODE_MENU;
        UNLOCKLV();
        break;
      case MODE_GALLERY:
      case MODE_GALLERY_MENU:
        menu_gallery_loop(true); // 在这里处理事件
        break;
      case MODE_OSD_SETTINGS:
        LOCKLV();
        menu_osd_hide();
        UNLOCKLV();
        current_mode = MODE_MAIN;
        break;
      case MODE_CAMERA_SETTINGS:
        LOCKLV();
        menu_camera_hide();
        UNLOCKLV();
        current_mode = MODE_MAIN;
        break;
      case MODE_SYSTEM_SETTINGS:
        LOCKLV();
        menu_system_hide();
        UNLOCKLV();
        current_mode = MODE_MAIN;
        break;
      default:
        break;
      }
    } else {
      if (card_menuPage.obj != NULL && lv_obj_is_valid(card_menuPage.obj)) {
        if (lv_obj_get_width(card_menuPage.obj) == 0) {
          // 已收起，删除widget
          LOCKLV();
          lv_obj_del_delayed(card_menuPage.obj, 500);
          card_menuPage.obj = NULL;
          UNLOCKLV();
        }
      }
    }
  } else {
    if (close_for_opening_submenu || HAL::key_press_event[1]) {
      if (!close_for_opening_submenu) {
        current_mode = MODE_MAIN;
      } else {
        switch (selected_menu_number) {
        case BUTTON_GALLERY:
          current_mode = MODE_GALLERY;
          menu_gallery_show(); // 这里不需要锁定UI线程
          break;
        case BUTTON_OSD:
          current_mode = MODE_OSD_SETTINGS;
          LOCKLV();
          menu_osd_show();
          UNLOCKLV();
          break;
        case BUTTON_CAMERA:
          current_mode = MODE_CAMERA_SETTINGS;
          LOCKLV();
          menu_camera_show();
          UNLOCKLV();
          break;
        case BUTTON_SYSTEM:
          current_mode = MODE_SYSTEM_SETTINGS;
          LOCKLV();
          menu_system_show();
          UNLOCKLV();
          break;
        default:
          current_mode = MODE_MAIN;
          break;
        }
      }
      selected_menu_number = BUTTON_DEFAULT;
      close_for_opening_submenu = false;
      HAL::key_press_event[1] = false;
      expanded = false;
      LOCKLV();
      menu_hide();
      UNLOCKLV();
    }
  }
}