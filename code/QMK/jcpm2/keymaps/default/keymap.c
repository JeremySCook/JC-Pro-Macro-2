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
        KC_MUTE,       KC_X,     LSFT(KC_COMM),    LSFT(KC_DOT),
        DF(_LAYER1),   KC_X,     KC_J,             KC_L,
        KC_MPRV,       KC_MPLY,  KC_MNXT,          OSL(_LAYER0_MOD) // btm-right one shot mod layer
    ),
    [_LAYER0_MOD] = LAYOUT( // default MOD
        _______,            KC_X,     _______,    _______, // _______ transparent, goes to above layer
        _______,            KC_X,     _______,    _______,
        C(LGUI(KC_SPC)),    _______,  _______,    UG_TOGG
    ),
    [_LAYER1] = LAYOUT( // FCPX
        LSFT(LGUI(KC_B)),  KC_X,     LGUI(KC_B), LGUI(KC_EQL),
        DF(_LAYER2),       KC_X,     LALT(KC_K), LGUI(KC_MINS),
        KC_J,              KC_K,     KC_L,       KC_BSPC
    ),
    [_LAYER2] = LAYOUT( // KICAD
        KC_E,           KC_X,     KC_ESC,     KC_M,
        DF(_LAYER0),    KC_X,     LGUI(KC_Z), KC_X,
        KC_V,           KC_D,     KC_U,       KC_BSPC    ),
};

#ifdef ENCODER_MAP_ENABLE //defined in rules.mk
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_LAYER0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }, // default
    [_LAYER0_MOD] = { ENCODER_CCW_CW(_______, _______) }, // default MOD
    [_LAYER1] = { ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) }, // FCPX
    [_LAYER2] = { ENCODER_CCW_CW(KC_R, S(KC_R)) }, // KICAD
};
#endif