//
// Created by dudu233 on 2025/10/10.
//

#pragma once

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>

typedef int32_t s32;
typedef uint32_t u32;

#include <sunxi_display2.h>
#include <sys/ioctl.h>
#include <unistd.h>

void backlight_init();
int backlight_get();
void backlight_set(int new_backlight);