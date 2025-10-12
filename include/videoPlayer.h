#pragma once

#include "cameraUtils.h"
#include "lvgl.h"
#include "settings.h"
#include "ui/animations.h"
#include "ui/lock.h"
#include "videoCodec.h"

#include <semaphore.h>
#include <sys/time.h>
#include <unistd.h>

#define CMD_NONE 0
#define CMD_CONNECT 1
#define CMD_PLAY 2
#define CMD_PAUSE 3
#define CMD_DISCONNECT 4

#define STATE_IDLE 1
#define STATE_PLAYING 2
#define STATE_PAUSED 3

class VideoPlayer {
private:
public:
  // cv::VideoCapture video;
  lv_obj_t *img_obj;
  void init();
  void connect();
  void play();
  void disconnect();
};

extern VideoPlayer videoPlayer;