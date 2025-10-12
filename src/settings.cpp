#include "settings.h"

settingsStorage_t globalSettings;
void settings_default() {
  globalSettings.__head = SETTINGS_HEAD;
  globalSettings.brightness = 170;
  globalSettings.colorPalette = IR_COLOR_PALETTE_DEFAULT;
  globalSettings.enableGraph = false;
  globalSettings.graphPos = 0;
  globalSettings.graphRefreshInterval = 0;
  globalSettings.graphSize = 0;
  globalSettings.enableMaxValueDisplay = false;
  globalSettings.enableMinValueDisplay = false;
  globalSettings.enableCenterValueDisplay = true;
  globalSettings.preserveOSD = false;
  globalSettings.useBuildinCursors = false;
  globalSettings.displayBattery = true;
  globalSettings.pictureFormat = jpeg_raw;
  globalSettings.videoFormat = mp4_mjpeg;
  globalSettings.__tail = SETTINGS_TAIL;
}

void settings_load() {
  FILE *fp = fopen(SETTINGS_PATH, "rb");
  if (fp == NULL) {
    printf("[Warning] No settings file\n");
    settings_default();
    settings_save();
    return;
  }
  memset(&globalSettings, 0, sizeof(globalSettings));
  fread(&globalSettings, sizeof(globalSettings), 1, fp);
  fclose(fp);
  if (globalSettings.__tail != SETTINGS_TAIL ||
      globalSettings.__head != SETTINGS_HEAD) {
    printf("[Warning] Corrupted settings storage\n");
    settings_default();
    settings_save();
  }
}

void settings_save() {
  FILE *fp = fopen(SETTINGS_PATH, "wb");
  if (fp == NULL) {
    printf("[Error] Unable to save settings\n");
    return;
  }
  fwrite(&globalSettings, sizeof(globalSettings), 1, fp);
  fclose(fp);
}
