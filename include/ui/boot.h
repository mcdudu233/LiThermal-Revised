//
// Created by dudu233 on 2025/10/12.
//

#pragma once

#include "cameraUtils.h"
#include "lvgl.h"
#include "ui/imgs.h"
#include "ui/lottie.h"
#include "videoPlayer.h"

#include <rlottie_inc/rlottie_capi.h>

#define STAGE_LOAD_NCM_PCT_START 0
#define STAGE_LOAD_NCM_PCT_STEP 20
#define STAGE_LOAD_HTTP_PCT_START 380
#define STAGE_LOAD_HTTP_PCT_STEP 20
#define STAGE_LOAD_BAR_TOTAL 880

#define STAGE_FIRST 0
#define STAGE_WAIT_NCM 1
#define STAGE_WAIT_HTTP 2
#define STAGE_FIN 3

void boot_load(lv_obj_t *parent);
