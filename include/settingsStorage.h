#pragma once
#include <stdint.h>

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
  uint32_t enableMaxValueDisplay;
  uint32_t enableMinValueDisplay;
  uint32_t enableCenterValueDisplay;
  uint32_t preserveOSD;
  uint32_t useBuildinCursors;
  uint32_t displayBattery;

  uint32_t pictureFormat;
  uint32_t videoFormat;

  uint32_t __tail;
} settingsStorage_t;
extern settingsStorage_t globalSettings;
#define GRAPH_DATA_SOURCE_MAX 0
#define GRAPH_DATA_SOURCE_MIN 1

void settings_default();
void settings_load();
void settings_save();
