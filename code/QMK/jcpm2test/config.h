// I2C Configuration
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN D0
#define I2C1_SDA_PIN D1
#define I2C1_SPEED 400000

// OLED Configuration
#define OLED_DISPLAY_128x64
#define OLED_DISPLAY_ADDRESS 0x3C //correct per Arduino code
#define OLED_TIMEOUT 300000

// OLED Configuration
#define NUM_ENCODERS 1
#define NUM_DIRECTIONS 2
#define ENCODER_A_PINS { D2 }
#define ENCODER_B_PINS { D3 }

// LIGHTING Configuration
#define WS2812_DI_PIN C6
#define RGBLIGHT_LED_COUNT 12
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LIMIT_VAL 60