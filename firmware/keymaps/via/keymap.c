#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_5,    KC_4,    KC_3,    KC_2,    KC_1,    KC_ESC,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_T,    KC_R,    KC_E,    KC_W,    KC_Q,    KC_TAB,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
        KC_G,    KC_F,    KC_D,    KC_S,    KC_A,    KC_GRV,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_B,    KC_V,    KC_C,    KC_X,    KC_Z,    KC_LSFT,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                   KC_BSPC, KC_DEL,                                KC_LBRC, KC_RBRC,
                          LOWER,   KC_SPC,  KC_ENT,                       KC_ENT,  KC_SPC,  RAISE,
                                   KC_LGUI, KC_LALT,                               KC_RALT, KC_RGUI
    ),

    [_LOWER] = LAYOUT(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        _______, _______, _______, _______, _______, _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, _______,
        _______, _______, _______, KC_LSFT, KC_LCTL, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______,                             _______, _______,
                          _______, _______, _______,                    _______, _______, _______,
                                   _______, _______,                             _______, _______
    ),

    [_RAISE] = LAYOUT(
        KC_F5,   KC_F4,   KC_F3,   KC_F2,   KC_F1,   KC_F11,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
        _______, _______, _______, _______, _______, _______, KC_PAST, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______,
        _______, _______, _______, _______, _______, _______, KC_PSLS, KC_P4,   KC_P5,   KC_P6,   KC_PMNS, _______,
        _______, _______, _______, _______, _______, _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PDOT, _______,
                                   _______, _______,                             _______, _______,
                          _______, _______, _______,                    _______, _______, _______,
                                   _______, _______,                             _______, _______
    ),

    [_ADJUST] = LAYOUT(
        _______, _______, _______, _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU,
        _______, RGB_MOD, RGB_SAD, RGB_VAD, _______, _______, NK_TOGG, _______, _______, _______, _______, _______,
                                   _______, _______,                             _______, _______,
                          _______, _______, _______,                    _______, _______, _______,
                                   _______, _______,                             _______, _______
    ),
};
