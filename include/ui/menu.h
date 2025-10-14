//
// Created by dudu233 on 2025/10/10.
//

#pragma once

#include "lvgl.h"
#include "ui/menu/camera.h"
#include "ui/menu/gallery.h"
#include "ui/menu/osd.h"
#include "ui/menu/system.h"

#define MENU_BOX_WIDTH 290
#define MENU_BOX_HEIGHT 136
#define MENU_BOX_Y_SHOW 30
#define MENU_BUTTON_WIDTH_DEFAULT 60
#define MENU_BUTTON_HEIGHT_DEFAULT 100
#define MENU_BUTTON_WIDTH_FOCUSED 70
#define MENU_BUTTON_HEIGHT_FOCUSED 110

typedef enum {
  BUTTON_DEFAULT = 0,
  BUTTON_GALLERY = 1,
  BUTTON_OSD = 2,
  BUTTON_CAMERA = 3,
  BUTTON_SYSTEM = 4,
} button_mode_t;

void menu_show();
void menu_hide();
void menu_loop();