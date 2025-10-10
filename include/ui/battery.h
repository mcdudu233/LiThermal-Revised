//
// Created by dudu233 on 2025/10/10.
//

#pragma once

#include "PowerManager.h"
#include "my_main.h"

#define BATTERY_CARD_X 268
#define BATTERY_CARD_SHOW_Y -13
#define BATTERY_CARD_HIDE_Y -43
#define BATTERY_CARD_WIDTH 50
#define BATTERY_CARD_HEIGHT 33

#define BATTERY_OUTLINE_WIDTH 38  // 电池图标宽度
#define BATTERY_OUTLINE_HEIGHT 18 // 电池图标高度

// 充电图标
extern "C" const lv_img_dsc_t bolt;

void battery_show();
void battery_hide();
void battery_loop();