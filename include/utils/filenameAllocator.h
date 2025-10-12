#pragma once

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "settings.h"

#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define GALLERY_MAX_IMAGES 100000 // 必须为8的倍数

int getTotalImages();
int getLastImageID();
int getNextImage(int current);
int getPrevImage(int current);
void readFiles(const char *dirToOpen);
const char *allocateNewFilename();
void freeFileName(int id);
