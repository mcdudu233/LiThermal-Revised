//
// Created by dudu233 on 2025/10/12.
//

#pragma once

#include "cameraUtils.h"
#include "lvgl.h"
#include "myHAL.h"
#include "settings.h"
#include "ui/animations.h"
#include "ui/lock.h"

#include <cmath>

#define CARD_SIZE_SMALL_WIDTH 120
#define CARD_SIZE_LARGE_WIDTH 240
#define CARD_SIZE_HEIGHT 120

#define GRAPH_SIZE_SMALL false
#define GRAPH_SIZE_LAEGE true

typedef uint16_t (*MyChartGetValueCallback)(int id); // 获取数据的回调函数

class MyChart {
public:
  lv_obj_t *_chart_widget = NULL;
  lv_chart_series_t *_series = NULL;
  lv_chart_series_t *_series2 = NULL;
  uint16_t _width;
  uint16_t _height;
  uint16_t _data_buffer[2];      //[0]为上一次数据，[1]为当前数据, 0..1000
  uint16_t _data_buffer2[2];     //[0]为上一次数据，[1]为当前数据, 0..1000
  uint16_t _data_weight_current; // 记录距离上一次获取数据以来的图表刷新次数
  uint16_t _data_weight_max;     // 记录插值次数
  uint16_t _data_count;
  uint16_t _data_interval;
  MyChartGetValueCallback _callback;
  lv_timer_t *_timer = NULL;
  lv_obj_t *label = NULL;
  float label_factor = 1.0;
  lv_obj_t *lbl_title = NULL;
  uint16_t _update_interval = 20;
  void init(lv_obj_t *parent, uint16_t width, uint16_t height,
            uint16_t data_interval, uint16_t default_value,
            MyChartGetValueCallback callback, uint16_t update_interval = 20);
  void destroy();
  void showLabel(bool show);
  void showTitle(const char *title);
  uint16_t cosineInterpolation(uint16_t data_buffer_ptr[2]);
};

void graph_show();
void graph_loop();