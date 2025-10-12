#include "ui/battery.h"

static MyCard cardBattery;
static lv_obj_t *imgBolt = NULL;
static lv_obj_t *objBattery = NULL;

static bool expanded = false;
static void battery_construct(lv_obj_t *parent) {
  lv_obj_clear_flag(parent, LV_OBJ_FLAG_SCROLLABLE); /// Flags
  lv_obj_set_style_bg_opa(parent, LV_OPA_0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(parent, 0, 0);

  //  lv_obj_t *lbl_battery = lv_label_create(parent);
  //  lv_obj_set_align(lbl_battery, LV_ALIGN_TOP_RIGHT);
  //  lv_obj_set_x(lbl_battery, -7);
  //  lv_label_set_text(lbl_battery, "0.00V");

  // 电池电量外边框
  lv_obj_t *objBatteryOutline = lv_obj_create(parent);
  lv_obj_set_style_border_width(objBatteryOutline, 2, 0);
  lv_obj_set_style_pad_all(objBatteryOutline, 0, 0);
  lv_obj_set_style_radius(objBatteryOutline, 8, 0);
  lv_obj_clear_flag(objBatteryOutline, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_size(objBatteryOutline, BATTERY_OUTLINE_WIDTH,
                  BATTERY_OUTLINE_HEIGHT);
  lv_obj_align(objBatteryOutline, LV_ALIGN_TOP_LEFT, 0, 0);

  // 电池电量填充
  objBattery = lv_obj_create(objBatteryOutline);
  lv_obj_set_style_outline_width(objBattery, 0, 0);
  lv_obj_set_style_outline_pad(objBattery, 0, 0);
  lv_obj_set_style_border_width(objBattery, 0, 0);
  lv_obj_set_style_bg_color(objBattery, lv_color_hex(0xff0000), 0);
  lv_obj_set_size(objBattery, BATTERY_OUTLINE_WIDTH,
                  BATTERY_OUTLINE_HEIGHT - 4);
  lv_obj_set_style_border_width(objBattery, 0, 0);
  lv_obj_set_style_radius(objBattery, 8, 0);
  lv_obj_align(objBattery, LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_clear_flag(objBattery, LV_OBJ_FLAG_SCROLLABLE);

  // 电池百分比
  lv_obj_t *objBatteryLabel = lv_label_create(objBatteryOutline);
  lv_obj_align(objBatteryLabel, LV_ALIGN_CENTER, 0, 0);

  imgBolt = lv_img_create(parent);
  lv_obj_set_align(imgBolt, LV_ALIGN_TOP_LEFT);
  lv_img_set_src(imgBolt, &bolt);
  lv_obj_set_pos(imgBolt, 13, 2);
  lv_obj_set_style_opa(imgBolt, 0, 0);
}

void battery_show() {
  if (cardBattery.obj == NULL || !lv_obj_is_valid(cardBattery.obj)) {
    cardBattery.create(lv_layer_sys(), BATTERY_CARD_X, BATTERY_CARD_HIDE_Y,
                       BATTERY_CARD_WIDTH, BATTERY_CARD_HEIGHT,
                       LV_ALIGN_TOP_LEFT);
    cardBattery.show(CARD_ANIM_NONE);
    battery_construct(cardBattery.obj);
  }
  cardBattery.move(BATTERY_CARD_X, BATTERY_CARD_SHOW_Y);
}

void battery_hide() { cardBattery.move(BATTERY_CARD_X, BATTERY_CARD_HIDE_Y); }

static int last_battery = 101;
void battery_loop() {
  static int cnt = 0;
  static bool last_charging = false;
  if (globalSettings.displayBattery || current_mode == MODE_MAINMENU) {
    if (!expanded) {
      expanded = true;
      LOCKLV();
      battery_show();
      UNLOCKLV();
      cnt = 100;
    }
    ++cnt;
    if (cnt >= 100) {
      int16_t voltage = PowerManager_getBatteryVoltage();
      bool charging = PowerManager_isCharging();
      if (voltage > 0) {
        int percent =
            (int)((voltage / 1000.0 - BATTERY_VOLTAGE_MIN) /
                  (BATTERY_VOLTAGE_MAX - BATTERY_VOLTAGE_MIN) * 100.0);
        if (percent < 0) {
          percent = 0;
        } else if (percent > 100) {
          percent = 100;
        }

        if (charging != last_charging) {
          last_charging = charging;
          if (charging) {
            // 显示为充电中
            lv_obj_fade_in(imgBolt, 500, 0);
          } else {
            lv_obj_fade_out(imgBolt, 300, 0);
          }
          last_battery = 101;
        }
        // 保证电量显示稳定
        if (percent < last_battery) {
          last_battery = percent;
          // TODO 低电量关机
          //          if (percent < 5) {
          //          }

          LOCKLV();
          //        lv_label_set_text_fmt(lv_obj_get_child(cardBattery.obj, 0),
          //        "%d.%02dV",
          //                              voltage / 1000, voltage % 1000 / 10);
          // 设置电量颜色
          if (percent <= 20) {
            lv_obj_set_style_bg_color(objBattery, lv_color_hex(0xff0000), 0);
          } else {
            lv_obj_set_style_bg_color(objBattery, lv_color_hex(0x00ff00), 0);
          }
          // 修改电量颜色宽度
          lv_obj_set_width(objBattery,
                           BATTERY_OUTLINE_WIDTH * percent / 100 - 1);
          // 修改电池百分比
          lv_obj_t *text = lv_obj_get_child(lv_obj_get_parent(objBattery), -1);
          if (charging) {
            lv_label_set_text_fmt(text, "");
          } else {
            lv_label_set_text_fmt(text, "%d", (int)percent);
          }
          UNLOCKLV();
        }
      }
      cnt = 0;
    }
  } else {
    if (expanded) {
      expanded = false;
      LOCKLV();
      battery_hide();
      UNLOCKLV();
    }
  }
}