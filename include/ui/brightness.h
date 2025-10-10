//
// Created by dudu233 on 2025/10/10.
//

#pragma once

#include "backlight.h"
#include "my_main.h"

#define UI_BRIGHTNESSBAR_Y -40
#define UI_BRIGHTNESSBAR_X_HIDE 50
#define UI_BRIGHTNESSBAR_X_SHOW -10
#define UI_BRIGHTNESSBAR_HEIGHT_HIDE 60
#define UI_BRIGHTNESSBAR_HEIGHT_SHOW 102
#define BRIGHTNESSBAR_AUTO_HIDE_TIME 1 // auto hide when inactive for 2s

void brightness_show();
void brightness_hide();
void brightness_loop();