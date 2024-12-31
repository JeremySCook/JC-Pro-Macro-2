#include QMK_KEYBOARD_H

// Define the layers
enum custom_layers {
    _LAYER0,
    _LAYER1,
    _LAYER2,
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
     * │ E │ n │ 6 │ 7 │
     * ├───┼───┼───┼───┤
     * │ B │ n │ 5 │ 8 │
     * ├───┼───┼───┼───┤
     * │ 2 │ 3 │ 4 │ 9 │
     * └───┴───┴───┴───┘
     */
    [_LAYER0] = LAYOUT(
        KC_MUTE,        KC_X,     LSFT(KC_COMM),    LSFT(KC_DOT),
        LAYER_TOGGLE,   KC_X,     KC_J,             KC_L,
        KC_MPRV,        KC_MPLY,  KC_MNXT,          UG_TOGG
    ),
    [_LAYER1] = LAYOUT(
        KC_P1,          KC_X,     KC_P1,      KC_P7,
        LAYER_TOGGLE,   KC_X,     KC_P5,      KC_P8,
        KC_P2,          KC_P3,    KC_P4,      KC_P9
    ),
    [_LAYER2] = LAYOUT(
        KC_P2,          KC_X,     KC_P2,      KC_P7,
        LAYER_TOGGLE,   KC_X,     KC_P5,      KC_P8,
        KC_P2,          KC_P3,    KC_P4,      KC_P9
    ),
};

#ifdef ENCODER_MAP_ENABLE //defined in rules.mk
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_LAYER0] = { ENCODER_CCW_CW(KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP) },
    [_LAYER1] = { ENCODER_CCW_CW(KC_C, KC_D) },
    [_LAYER2] = { ENCODER_CCW_CW(KC_E, KC_F) },
};
#endif

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
// Function to display the current layer and information on the OLED
bool oled_task_user(void) {
    // Need to Rotate OLED 180 degrees, haven't yet figured this out

    // Display a title or heading
    oled_write_ln_P(PSTR("Keyboard Info:"), false);

    // Display the current layer
    oled_write_ln_P(PSTR("Layer:"), false);
    switch (get_highest_layer(layer_state)) {
        case _LAYER0:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case _LAYER1:
            oled_write_ln_P(PSTR("Layer 1"), false);
            break;
        case _LAYER2:
            oled_write_ln_P(PSTR("Layer 2"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Unknown"), false);
            break;
    }

    // Optionally display other custom text
    oled_write_ln_P(PSTR("Enc Vol +/-"), false);

    return false; // Indicate that no further OLED updates are required
}
#endif