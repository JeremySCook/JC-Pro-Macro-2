#pragma once

// I2C Configuration
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN D0
#define I2C1_SDA_PIN D1

// OLED Configuration
#define OLED_DISPLAY_128X64
#define OLED_DISPLAY_ADDRESS 0x3C //correct per Arduino code
#define OLED_TIMEOUT 2000000

// Encoder Configuration
//#define NUM_ENCODERS 1
//#define NUM_DIRECTIONS 2
#define ENCODER_RESOLUTION 4
#define ENCODER_A_PINS { D2 }
#define ENCODER_B_PINS { D3 }

// LIGHTING Configuration
#define WS2812_DI_PIN C6
#define RGB_MATRIX_LED_COUNT 12
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 5
#define RGB_MATRIX_DEFAULT_ON false