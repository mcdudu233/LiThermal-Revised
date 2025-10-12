//
// Created by dudu233 on 2025/10/10.
//

#pragma once

#include "lvgl.h"
#include "ui/menu/basic.h"
#include "ui/menu/gallery.h"
#include "ui/menu/system.h"

#define MENU_BOX_WIDHT 230
#define MENU_BOX_HEIGHT 136
#define MENU_BOX_Y_SHOW 30
#define MENU_BUTTON_WIDTH_DEFAULT 60
#define MENU_BUTTON_HEIGHT_DEFAULT 100
#define MENU_BUTTON_WIDTH_FOCUSED 70
#define MENU_BUTTON_HEIGHT_FOCUSED 110

void menu_show();
void menu_hide();
void menu_loop();