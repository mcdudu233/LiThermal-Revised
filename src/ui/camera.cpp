#include <my_main.h>
static void flash_bang_effect() {
  LOCKLV();
  lv_obj_t *mask_camera = lv_obj_create(lv_scr_act());
  lv_obj_set_size(mask_camera, 320, 240);
  lv_obj_set_style_border_width(mask_camera, 0, 0);
  lv_obj_set_style_bg_color(mask_camera, lv_color_black(), 0);
  lv_obj_set_style_radius(mask_camera, 0, 0);
  lv_obj_set_style_opa(mask_camera, 128, 0);
  lv_obj_fade_out(mask_camera, 300, 0);
  lv_obj_del_delayed(mask_camera, 300);
  UNLOCKLV();
}
#define TJE_IMPLEMENTATION
#include "utils/tiny_jpeg.h"
void camera_take_photo_from_stream() {
  if (cameraUtils.connected == false)
    return;
  switch (globalSettings.pictureFormat) {
  case jpeg: {
    if (globalSettings.preserveOSD) {
      char data[128];
      sprintf(data, "%s.jpeg", allocateNewFilename());
      LOCKLV();
      lv_img_dsc_t *snapshot =
          lv_snapshot_take(lv_scr_act(), LV_IMG_CF_TRUE_COLOR);
      tje_encode_to_file(data, 320, 240, 4, snapshot->data);
      lv_snapshot_free(snapshot);
      UNLOCKLV();
    } else {
      cameraUtils.saveJpegWithExtra(allocateNewFilename(), true, false);
    }
    break;
  }
  case raw: {
    cameraUtils.saveJpegWithExtra(allocateNewFilename(), false, true);
    break;
  }
  case jpeg_raw: {
    if (globalSettings.preserveOSD) {
      char data[128];
      sprintf(data, "%s.jpeg", allocateNewFilename());
      LOCKLV();
      lv_img_dsc_t *snapshot =
          lv_snapshot_take(lv_scr_act(), LV_IMG_CF_TRUE_COLOR);
      tje_encode_to_file(data, 320, 240, 4, snapshot->data);
      lv_snapshot_free(snapshot);
      UNLOCKLV();
      cameraUtils.saveJpegWithExtra(allocateNewFilename(), false, true);
    } else {
      cameraUtils.saveJpegWithExtra(allocateNewFilename(), true, true);
    }
    break;
  }
  }
  flash_bang_effect();
}
#include "lottie_rec.h"
extern bool packet_dumping;
lv_timer_t *tm_create_circle = NULL, *tm_circle = NULL;
lv_obj_t *circle_REC = NULL;
lv_obj_t *lot_rec = NULL;
void camera_record_toggle_dump_stream() {
  if (cameraUtils.connected == false)
    return;
  if (packet_dumping == true) {
    flash_bang_effect();
    LOCKLV();
    if (tm_create_circle) {
      lv_timer_del(tm_create_circle);
      tm_create_circle = NULL;
    }
    if (tm_circle) {
      lv_timer_del(tm_circle);
      tm_circle = NULL;
    }
    if (lv_obj_is_valid(circle_REC)) {
      lv_obj_del(circle_REC);
      circle_REC = NULL;
    }
    if (lv_obj_is_valid(lot_rec)) {
      lv_obj_del(lot_rec);
      lot_rec = NULL;
    }
    UNLOCKLV();
    codec_enablePacketDumping(false, NULL);
  } else {
    const char *name_partial = allocateNewFilename();
    if (name_partial == NULL) {
      // TODO: 添加错误提示
      return;
    }

    // 保留视频开头截图 用于显示
    if (globalSettings.preserveOSD) {
      char data[128];
      sprintf(data, "%s.jpeg", name_partial);
      LOCKLV();
      lv_img_dsc_t *snapshot =
          lv_snapshot_take(lv_scr_act(), LV_IMG_CF_TRUE_COLOR);
      tje_encode_to_file(data, 320, 240, 4, snapshot->data);
      lv_snapshot_free(snapshot);
      UNLOCKLV();
    } else {
      cameraUtils.saveJpegWithExtra(name_partial, true, false);
    }

    // 录制视频
    switch (globalSettings.videoFormat) {
    case mp4: {
      codec_enablePacketDumping(true, name_partial, true, false);
      break;
    }
    case mjpeg: {
      codec_enablePacketDumping(true, name_partial, false, true);
      break;
    }
    case mp4_mjpeg: {
      codec_enablePacketDumping(true, name_partial, true, true);
      break;
    }
    }

    // 动画效果
    LOCKLV();
    lot_rec = lv_rlottie_create_from_raw(lv_layer_top(), 200, 200, lottie_rec);
    lv_obj_center(lot_rec);
    lv_rlottie_set_play_mode(lot_rec, LV_RLOTTIE_CTRL_PLAY);
    lv_obj_del_delayed(lot_rec, 2000);
    UNLOCKLV();
    tm_create_circle = lv_timer_create(
        [](lv_timer_t *tm_out) {
          circle_REC = lv_obj_create(lv_layer_top());
          lv_obj_set_size(circle_REC, 8, 8);
          lv_obj_align(circle_REC, LV_ALIGN_TOP_RIGHT, -8, 8);
          lv_obj_set_style_radius(circle_REC, LV_RADIUS_CIRCLE, 0);
          lv_obj_set_style_border_width(circle_REC, 0, 0);
          lv_obj_set_style_bg_color(circle_REC, lv_color_hex(0xFF0000), 0);
          lv_obj_fade_in(circle_REC, 700, 0);
          tm_circle = lv_timer_create(
              [](lv_timer_t *tm) {
                if (lv_obj_is_valid(circle_REC) == false) {
                  lv_timer_del(tm);
                  circle_REC = NULL;
                  return;
                }
                if (lv_obj_get_style_opa(circle_REC, 0) <= 5) {
                  lv_obj_fade_in(circle_REC, 700, 0);
                } else {
                  lv_obj_fade_out(circle_REC, 700, 0);
                }
              },
              700, NULL);
          lv_timer_del(tm_create_circle);
          tm_create_circle = NULL;
        },
        1800, 0);
  }
}
