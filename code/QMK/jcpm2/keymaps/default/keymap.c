// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Define the layers
enum layer_names {
    _LAYER0,
    _LAYER0_MOD,
    _LAYER1,
    _LAYER2,
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
    [_LAYER0] = LAYOUT( // default
        KC_MUTE,                 LSFT(KC_COMM),    LSFT(KC_DOT),
        DF(_LAYER1),             KC_J,             KC_L,
        KC_MPRV,       KC_MPLY,  KC_MNXT,          OSL(_LAYER0_MOD) // btm-right one shot mod layer
    ),
    [_LAYER0_MOD] = LAYOUT( // default MOD
        _______,                      _______,    _______, // _______ transparent, goes to above layer
        _______,                      _______,    _______,
        C(LGUI(KC_SPC)),    _______,  _______,    UG_TOGG
    ),
    [_LAYER1] = LAYOUT( // FCPX
        LSFT(LGUI(KC_B)),            LGUI(KC_B), LGUI(KC_EQL),
        DF(_LAYER2),                 LALT(KC_K), LGUI(KC_MINS),
        KC_J,              KC_K,     KC_L,       KC_BSPC
    ),
    [_LAYER2] = LAYOUT( // KICAD
        KC_E,                        KC_ESC,     KC_M,
        DF(_LAYER0),                 LGUI(KC_Z), KC_X,
        KC_V,              KC_D,     KC_U,       KC_BSPC    ),
};

#ifdef ENCODER_MAP_ENABLE //defined in rules.mk
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_LAYER0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }, // default
    [_LAYER0_MOD] = { ENCODER_CCW_CW(_______, _______) }, // default MOD
    [_LAYER1] = { ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) }, // FCPX
    [_LAYER2] = { ENCODER_CCW_CW(KC_R, S(KC_R)) }, // KICAD
};
#endif

#ifdef OLED_ENABLE
// Function to display the current layer and information on the OLED
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }

bool oled_task_user(void) {
    switch (get_highest_layer(layer_state)) {
        case _LAYER0:
            oled_write_ln_P(PSTR("(VOL- VOL+)  LAYER0"), false);
            oled_write_ln_P(PSTR(""), false);
            oled_write_ln_P(PSTR("MUTE      SLOW FAST"), false);
            oled_write_ln_P(PSTR(""), false);
            oled_write_ln_P(PSTR("LAYR RSET 10BK 10FW"), false);
            oled_write_ln_P(PSTR(""), false);
            oled_write_ln_P(PSTR("MREV MPLA MFWD EMOJ"), false);
            break;
        case _LAYER0_MOD:
            oled_write_ln_P(PSTR("____ ____      0-MOD"), false);
            oled_write_ln_P(PSTR(""), false);
            oled_write_ln_P(PSTR("____      ____ ____"), false);
            oled_write_ln_P(PSTR(""), false);
            oled_write_ln_P(PSTR("____ ____ ____ ____"), false);
            oled_write_ln_P(PSTR(""), false);
            oled_write_ln_P(PSTR("EMOJ ____ ____ UNDG"), false);
            break;
        case _LAYER1:
            oled_write_ln_P(PSTR("(FRA- FRA+)    FCPX"), false);
            oled_write_ln_P(PSTR(""), false);
            oled_write_ln_P(PSTR("XXXX      BRAK ZOM+"), false);
            oled_write_ln_P(PSTR(""), false);
            oled_write_ln_P(PSTR("LAYR RSET KFRA ZOM-"), false);
            oled_write_ln_P(PSTR(""), false);
            oled_write_ln_P(PSTR("BACK STOP FORW DELT"), false);
            break;
        case _LAYER2:
            oled_write_ln_P(PSTR("(RO L RO R)   KICAD"), false);
            oled_write_ln_P(PSTR(""), false);
            oled_write_ln_P(PSTR("EDIT      ESCP MOVE"), false);
            oled_write_ln_P(PSTR(""), false);
            oled_write_ln_P(PSTR("LAYR RSET UNDO TRAK"), false);
            oled_write_ln_P(PSTR(""), false);
            oled_write_ln_P(PSTR("VIA  DRAG SALL DELT"), false);
            break;
    }

    // Optionally display other custom text
    //oled_write_ln_P(PSTR("Enc Vol +/-"), false);

    return false; // Indicate that no further OLED updates are required
}
#endif