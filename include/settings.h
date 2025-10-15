#pragma once

#include "cameraUtils.h"

#include <cstring>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 参数配置
#define VIDEO_STREAM_URL "rtsp://admin:Ab123456@192.168.64.64"

// 注意：图像命名格式固定为：CAP+5位数字.[jpeg/mjpeg]
#define SETTINGS_PATH "/mnt/UDISK/settings.dat"
#define GALLERY_PATH                                                           \
  "/mnt/UDISK/DCIM" // 如需修改存储位置，需同时修改 lv_conf.h: LV_FS_STDIO_PATH

#define GRAPH_DATA_SOURCE_MAX 0
#define GRAPH_DATA_SOURCE_MIN 1

#define SETTINGS_HEAD 0x80000001
#define SETTINGS_TAIL 0x1715600D

typedef enum pictureFormat_t { jpeg, raw, jpeg_raw } pictureFormat_t;
typedef enum videoFormat_t { mp4, mjpeg, mp4_mjpeg } videoFormat_t;

typedef struct settingsStorage_t {
  uint32_t __head;

  uint32_t brightness;
  uint32_t colorPalette;
  uint32_t enableGraph;
  uint32_t graphPos;
  uint32_t graphSize;
  uint32_t graphRefreshInterval;
  uint32_t cameraBrightness;
  uint32_t cameraContrast;
  uint32_t enableNoiseReduce;
  uint32_t noiseReduceLevel;
  uint32_t noiseReduceFrameLevel;
  uint32_t noiseReduceInterFrameLevel;
  uint32_t enableDetailEnhancement;
  uint32_t detailEnhancementLevel;
  uint32_t enableMaxValueDisplay;
  uint32_t enableMinValueDisplay;
  uint32_t enableAvgValueDisplay;
  uint32_t enableCenterValueDisplay;
  uint32_t preserveOSD;
  uint32_t useBuildinCursors;
  uint32_t displayBattery;

  uint32_t pictureFormat;
  uint32_t videoFormat;

  uint32_t __tail;
} settingsStorage_t;
extern settingsStorage_t globalSettings;

void settings_default();
void settings_load();
void settings_save();
