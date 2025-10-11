#pragma once

// C library headers
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
// Linux headers
#include <cerrno>  // Error integer and strerror() function
#include <fcntl.h> // Contains file controls like O_RDWR
#include <signal.h>
#include <sys/select.h>
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()

#define SERIAL_CMD_READ_ADC 0x58
#define SERIAL_CMD_POWEROFF 0x6a
#define SERIAL_CMD_USBMODE_NORMAL 0x11
#define SERIAL_CMD_USBMODE_WIFI_CAM 0x12
#define SERIAL_CMD_USBMODE_DIRECT 0x13
#define SERIAL_CMD_IS_CHARGING 0x59

// 压降偏移 (V)
#define VOLTAGE_OFFSET 0.0
#define VOLTAGE_EXTERNAL_OFFSET 0.36
#define VOLTAGE_INTERNAL_OFFSET 0.05
// 判断是否为锂电池界限
#define VOLTAGE_BATTERY 4.3

// 锂电池电压范围 (V)
#define BATTERY_VOLTAGE_MIN 3.2
#define BATTERY_VOLTAGE_MAX 4.2