#pragma once

#include "backlight.h"
#include "ui/battery.h"
#include "ui/brightness.h"
#include "ui/camera.h"
#include "ui/menu.h"
#include "ui/poweroff.h"
#include "videoPlayer.h"

#include "lv_drivers/display/sunxifb.h"
#include <csignal>
#include <ctime>
#include <linux/input.h>
#include <sys/time.h>
#include <unistd.h>

#define INPUT_DEVICE_ENCODER "/dev/input/event0"
#define INPUT_DEVICE_KEY "/dev/input/event2"

#define IF_CHECK_FILENAME "/proc/net/dev"
#define IF_CHECK_NAME "usb0"
#define IF_CHECK_MAX_SIZE 2048

namespace HAL {
extern bool key_pressed[3];
extern time_t key_pressed_start_time[3]; // 注意不包括Enter
extern bool key_press_event[4];          //  包括Enter
void init();
void lv_loop();
} // namespace HAL

typedef enum {
  MODE_MAINPAGE,
  MODE_MAINMENU,
  MODE_GALLERY,
  MODE_GALLERY_MENU,
  MODE_CAMERA_SETTINGS,
  MODE_SYSTEM_SETTINGS,
} current_mode_t;
extern current_mode_t current_mode; // 当前设备所处模式
extern int last_encoder_direction;  // 记录编码器变化，用于亮度调节或相册

extern bool global_poweroff_request;
