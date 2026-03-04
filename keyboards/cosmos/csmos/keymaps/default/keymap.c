#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
    //  outer --->                                  <--- inner         inner --->                                  <--- outer
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, 
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,  
        KC_LSFT, LGUI_T(KC_A),LALT_T(KC_S),LCTL_T(KC_D),LSFT_T(KC_F),ALL_T(KC_G),         ALL_T(KC_H),LSFT_T(KC_J),LCTL_T(KC_K),LALT_T(KC_L),LGUI_T(KC_COLON),KC_QUOT, 
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS, 
    //  5th column bottom
                          XXXXXXX, XXXXXXX,                                              KC_LBRC, KC_RBRC, 
    //  thumb top
                                   LT(1, KC_SPACE),KC_ESC,  KC_UP,            KC_LEFT, KC_TAB,  KC_BSPC, 
    //  thumb bottom
                                            KC_ENT,  KC_DOWN,          KC_RIGHT,KC_ENT
    ),

    [1] = LAYOUT(
    //  outer --->                                  <--- inner         inner --->                                  <--- outer
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,          KC_CUT,  KC_INS,  KC_UNDO, KC_AGIN, KC_DEL,  KC_WSCH, 
        XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_MUTE,          KC_COPY, KC_LEFT, KC_UP,   KC_DOWN, KC_RIGHT,XXXXXXX, 
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,          KC_PSTE, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  XXXXXXX, 
    //  5th column bottom
                          XXXXXXX, XXXXXXX,                                              XXXXXXX, XXXXXXX, 
    //  thumb top
                                   _______, _______, _______,          _______, _______, _______, 
    //  thumb bottom
                                            _______, _______,          _______, _______
    )

};
