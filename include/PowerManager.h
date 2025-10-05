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

// 二极管压降 (V)
#define VOLTAGE_OFFSET 0.55