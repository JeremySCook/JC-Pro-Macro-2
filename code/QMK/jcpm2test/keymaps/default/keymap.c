#include QMK_KEYBOARD_H

// Define the layers
enum custom_layers {
    _LAYER0,
    _LAYER1,
    _LAYER2,
    _LAYER3
};

// Layer state variable
uint8_t current_layer = _LAYER0;

// Keycodes for the 10 buttons
enum custom_keycodes {
    LAYER_TOGGLE = SAFE_RANGE,
    KEY1,
    KEY2,
    KEY3,
    KEY4,
    KEY5,
    KEY6,
    KEY7,
    KEY8,
    KEY9,
    KEY10,
    KEY11
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 0 │ n │ 6 │ 7 │
     * ├───┼───┼───┼───┤
     * │ 1 │ n │ 5 │ 8 │
     * ├───┼───┼───┼───┤
     * │ 2 │ 3 │ 4 │ 9 │
     * └───┴───┴───┴───┘
     */
    [_LAYER0] = LAYOUT(
        KC_P0, KC_OUT, KC_P0, KC_P7,
        LAYER_TOGGLE, KC_OUT, KC_P5, KC_P8,
        KC_P2, KC_P3, KC_P4, KC_P9
    ),
    [_LAYER1] = LAYOUT(
        KC_P1, KC_OUT, KC_P1, KC_P7,
        LAYER_TOGGLE, KC_OUT, KC_P5, KC_P8,
        KC_P2, KC_P3, KC_P4, KC_P9
    ),
    [_LAYER2] = LAYOUT(
        KC_P2, KC_OUT, KC_P2, KC_P7,
        LAYER_TOGGLE, KC_OUT, KC_P5, KC_P8,
        KC_P2, KC_P3, KC_P4, KC_P9
    ),
    [_LAYER3] = LAYOUT(
        KC_P3, KC_OUT, KC_P3, KC_P7,
        LAYER_TOGGLE, KC_OUT, KC_P5, KC_P8,
        KC_P2, KC_P3, KC_P4, KC_P9
    )
};

// Process custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case LAYER_TOGGLE:
                current_layer = (current_layer + 1) % 4;
                layer_move(current_layer);
                return false; // Skip default processing
        }
    }
    return true; // Process all other keycodes normally
}

void matrix_init_user(void) {
    layer_move(current_layer); // Initialize the default layer
}

void matrix_scan_user(void) {
    // Add custom matrix scanning code here if needed
}

void led_set_user(uint8_t usb_led) {
    // Add custom LED handling code here if needed
}


#ifdef OLED_ENABLE
#endif

#ifdef ENCODER_MAP_ENABLE
    ENCODER_CCW_CW(KC_VOLD, KC_VOLU);
#endif