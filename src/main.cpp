#include "main.h"

using namespace std;
// 热成像刷新线程
pthread_t thread_app;
void *thread_app_func(void *) {
  static int centerRefreshCounter = 0;
  static uint32_t last_color_palette = -1;
  static uint32_t last_camera_brightness = -1;
  static uint32_t last_camera_contrast = -1;
  static uint32_t last_enableNoiseReduce = -1;
  static uint32_t last_noiseReduceLevel = -1;
  static uint32_t last_noiseReduceFrameLevel = -1;
  static uint32_t last_noiseReduceInterFrameLevel = -1;
  static uint32_t last_enableDetailEnhancement = -1;
  static uint32_t last_detailEnhancementLevel = -1;
  static uint32_t last_use4117Cursors = -1;
  static uint32_t last_enableMinValueDisplay = -1;
  static uint32_t last_enableMaxValueDisplay = -1;
  static uint32_t last_enableAvgValueDisplay = -1;
  static uint32_t last_enableCenterValueDisplay = -1;
  while (!cameraUtils.connected)
    usleep(50000);
  LOCKLV();
  crosshairs_show();
  graph_show();
  UNLOCKLV();
  while (true) {
    if (last_color_palette != globalSettings.colorPalette) {
      last_color_palette = globalSettings.colorPalette;
      cameraUtils.setColorPalette(globalSettings.colorPalette);
    }
    if (last_camera_brightness != globalSettings.cameraBrightness ||
        last_camera_contrast != globalSettings.cameraContrast) {
      last_camera_brightness = globalSettings.cameraBrightness;
      last_camera_contrast = globalSettings.cameraContrast;
      cameraUtils.setBrightnessContrast(globalSettings.cameraBrightness,
                                        globalSettings.cameraContrast);
    }
    if (last_enableNoiseReduce != globalSettings.enableNoiseReduce) {
      last_enableNoiseReduce = globalSettings.enableNoiseReduce;
      last_noiseReduceLevel = globalSettings.noiseReduceLevel;
      last_noiseReduceFrameLevel = globalSettings.noiseReduceFrameLevel;
      last_noiseReduceInterFrameLevel =
          globalSettings.noiseReduceInterFrameLevel;
      if (last_enableNoiseReduce == IR_DNR_MODE_GENERAL) {
        cameraUtils.setDigitalNoiseReduce(IR_DNR_MODE_GENERAL,
                                          globalSettings.noiseReduceLevel, 0);
      } else if (last_enableNoiseReduce == IR_DNR_MODE_ADVANCED) {
        cameraUtils.setDigitalNoiseReduce(
            IR_DNR_MODE_GENERAL, globalSettings.noiseReduceFrameLevel,
            globalSettings.noiseReduceInterFrameLevel);
      } else {
        cameraUtils.setDigitalNoiseReduce(IR_DNR_MODE_CLOSE, 0, 0);
      }
    }
    if (last_noiseReduceLevel != globalSettings.noiseReduceLevel &&
        globalSettings.enableNoiseReduce == IR_DNR_MODE_GENERAL) {
      last_noiseReduceLevel = globalSettings.noiseReduceLevel;
      cameraUtils.setDigitalNoiseReduce(IR_DNR_MODE_GENERAL,
                                        globalSettings.noiseReduceLevel, 0);
    }
    if ((last_noiseReduceFrameLevel != globalSettings.noiseReduceFrameLevel ||
         last_noiseReduceInterFrameLevel !=
             globalSettings.noiseReduceInterFrameLevel) &&
        globalSettings.enableNoiseReduce == IR_DNR_MODE_ADVANCED) {
      last_noiseReduceFrameLevel = globalSettings.noiseReduceFrameLevel;
      last_noiseReduceInterFrameLevel =
          globalSettings.noiseReduceInterFrameLevel;
      cameraUtils.setDigitalNoiseReduce(
          IR_DNR_MODE_GENERAL, globalSettings.noiseReduceFrameLevel,
          globalSettings.noiseReduceInterFrameLevel);
    }
    if (last_enableDetailEnhancement !=
        globalSettings.enableDetailEnhancement) {
      last_enableDetailEnhancement = globalSettings.enableDetailEnhancement;
      last_detailEnhancementLevel = globalSettings.detailEnhancementLevel;
      cameraUtils.setDigitalDetailEnhancement(
          globalSettings.enableDetailEnhancement,
          globalSettings.detailEnhancementLevel);
    }
    if (last_detailEnhancementLevel != globalSettings.detailEnhancementLevel &&
        globalSettings.enableDetailEnhancement) {
      last_detailEnhancementLevel = globalSettings.detailEnhancementLevel;
      cameraUtils.setDigitalDetailEnhancement(
          globalSettings.enableDetailEnhancement,
          globalSettings.detailEnhancementLevel);
    }
    if (last_use4117Cursors != globalSettings.useBuildinCursors) {
      last_use4117Cursors = globalSettings.useBuildinCursors;
      if (last_use4117Cursors) {
        cameraUtils.set4117Cursor(globalSettings.enableMinValueDisplay,
                                  globalSettings.enableMaxValueDisplay,
                                  globalSettings.enableAvgValueDisplay);
        cameraUtils.setCenterMeasure(globalSettings.enableCenterValueDisplay);
      } else {
        cameraUtils.set4117Cursor(false, false, false);
        cameraUtils.setCenterMeasure(false);
      }
      last_enableMaxValueDisplay = globalSettings.enableMaxValueDisplay;
      last_enableMinValueDisplay = globalSettings.enableMinValueDisplay;
      last_enableAvgValueDisplay = globalSettings.enableAvgValueDisplay;
      last_enableCenterValueDisplay = globalSettings.enableCenterValueDisplay;
    }
    if (last_enableMaxValueDisplay != globalSettings.enableMaxValueDisplay ||
        last_enableMinValueDisplay != globalSettings.enableMinValueDisplay ||
        last_enableAvgValueDisplay != globalSettings.enableAvgValueDisplay ||
        last_enableCenterValueDisplay !=
            globalSettings.enableCenterValueDisplay) {
      if (globalSettings.useBuildinCursors) {
        cameraUtils.set4117Cursor(globalSettings.enableMinValueDisplay,
                                  globalSettings.enableMaxValueDisplay,
                                  globalSettings.enableAvgValueDisplay);
        cameraUtils.setCenterMeasure(globalSettings.enableCenterValueDisplay);
      }
      last_enableMaxValueDisplay = globalSettings.enableMaxValueDisplay;
      last_enableMinValueDisplay = globalSettings.enableMinValueDisplay;
      last_enableAvgValueDisplay = globalSettings.enableAvgValueDisplay;
      last_enableCenterValueDisplay = globalSettings.enableCenterValueDisplay;
    }

    crosshairs_loop();
    graph_loop();

    usleep(40000);
  }
}

uint64_t getTimeUS() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000L + tv.tv_usec;
}
// 热成像温度更新线程 5HZ~10HZ
pthread_t thread_temperature;
void *thread_temperature_func(void *) {
  while (!cameraUtils.connected)
    usleep(50000);
  int wait = 100;
  // uint64_t fps_start = getTimeUS();
  // int fps = 0;
  while (true) {
    uint64_t start = getTimeUS();
    // uint64_t fps_end = getTimeUS();
    // uint64_t fps_last = fps_end - fps_start;
    // if (fps_last > 1000 * 1000)
    // {
    //     printf("[TRACE] temperature time exceeded 1 second: %d \n", fps);
    //     fps_start = fps_end;
    //     fps = 0;
    // }
    // fps++;
    if (!globalSettings.useBuildinCursors) {
      if (globalSettings.enableMinValueDisplay ||
          globalSettings.enableMaxValueDisplay ||
          globalSettings.enableAvgValueDisplay) {
        cameraUtils.getTemperature();
        if (globalSettings.enableCenterValueDisplay) {
          wait = 200;
        } else {
          wait = 100;
        }
      }
    }
    uint64_t end = getTimeUS();
    uint64_t last = end - start;
    if (last < wait * 1000) {
      usleep(wait * 1000 - last);
    }
  }
}

// 热成像中心温度更新线程 2HZ
pthread_t thread_temperature_center;
void *thread_temperature_center_func(void *) {
  while (!cameraUtils.connected)
    usleep(50000);
  // uint64_t fps_start = getTimeUS();
  // int fps = 0;
  while (true) {
    uint64_t start = getTimeUS();
    // uint64_t fps_end = getTimeUS();
    // uint64_t fps_last = fps_end - fps_start;
    // if (fps_last > 1000 * 1000)
    // {
    //     printf("[TRACE] temperature_center time exceeded 1 second: %d \n",
    //     fps); fps_start = fps_end; fps = 0;
    // }
    // fps++;
    if (!globalSettings.useBuildinCursors &&
        globalSettings.enableCenterValueDisplay) {
      cameraUtils.getTemperatureCenter();
    }
    uint64_t end = getTimeUS();
    uint64_t last = end - start;
    if (last < 500 * 1000) {
      usleep(500 * 1000 - last);
    }
  }
}

// UI刷新线程
pthread_t thread_ui;
void *thread_ui_func(void *) { HAL::lv_loop(); }

// 自动配置端口映射
void port_forward() {
  system("echo 1 > /proc/sys/net/ipv4/ip_forward");
  system("sysctl -w net.ipv4.conf.all.route_localnet=1");
  system("modprobe iptable_nat");
  system("modprobe xt_nat");
  system("iptables -t nat -F");
  system("iptables -t nat -X");
  system("iptables -t nat -A OUTPUT -p tcp -d 127.0.0.1 --dport 80 -j DNAT "
         "--to 192.168.64.64:80");
  system("iptables -t nat -A POSTROUTING -p tcp -s 127.0.0.1 -d 192.168.64.64 "
         "--dport 80 -j SNAT --to 192.168.64.32");
  system("iptables -t nat -A OUTPUT -p tcp -d 127.0.0.1 --dport 554 -j DNAT "
         "--to 192.168.64.64:554");
  system("iptables -t nat -A POSTROUTING -p tcp -s 127.0.0.1 -d 192.168.64.64 "
         "--dport 554 -j SNAT --to 192.168.64.32");
}

int main() {
  port_forward();

  system("mkdir " GALLERY_PATH);
  pthread_mutex_init(&lv_mutex, NULL);
  HAL::init();
  readFiles(GALLERY_PATH);
  lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_clear_flag(lv_layer_sys(), LV_OBJ_FLAG_SCROLLABLE);
  printf("Loop begin\n");
  boot_load(lv_scr_act());
  pthread_create(&thread_ui, NULL, thread_ui_func, NULL);
  cameraUtils.initHTTPClient();
  pthread_create(&thread_app, NULL, thread_app_func, NULL);
  pthread_create(&thread_temperature, NULL, thread_temperature_func, NULL);
  pthread_create(&thread_temperature_center, NULL,
                 thread_temperature_center_func, NULL);
  void *result;
  pthread_join(thread_ui, &result);
  return 0;
}
