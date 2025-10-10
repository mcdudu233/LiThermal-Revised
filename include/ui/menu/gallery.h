//
// Created by dudu233 on 2025/10/10.
//

#pragma once

#include "my_main.h"

#define GALLERY_CARD_SHOW_Y -13
#define GALLERY_CARD_HIDE_Y -43
#define GALLERY_POS_RIGHT_X 400

typedef enum {
  GALLERY_STATE_LIST,
  GALLERY_STATE_FULLSCREEN,
  GALLERY_STATE_MENU,
} gallery_state_t;

typedef enum {
  PHOTO_TYPE_FILE_NOT_FOUND,
  PHOTO_TYPE_PICTURE_JPEG,
  PHOTO_TYPE_PICTURE_RAW,
  PHOTO_TYPE_VIDEO_MP4,
  PHOTO_TYPE_VIDEO_MJPEG,
} photo_type_t;

/// @brief 渲染图像/视频缩略图到canvas
/// @param obj_id 对应canvas在image_obj中的位置
extern "C" const lv_img_dsc_t video;
extern "C" const lv_img_dsc_t image;
extern "C" const lv_img_dsc_t imageraw;

void menu_gallery_loop(bool has_hal_go_back_event);
void menu_gallery_show();
void menu_gallery_hide();
