//
// Created by dudu233 on 2025/10/12.
//

#pragma once

#include <pthread.h>

// lvgl互斥锁
extern pthread_mutex_t lv_mutex;
#define LOCKLV() pthread_mutex_lock(&lv_mutex)
#define UNLOCKLV() pthread_mutex_unlock(&lv_mutex)