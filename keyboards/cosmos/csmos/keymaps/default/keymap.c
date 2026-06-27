#include QMK_KEYBOARD_H

// Layers: 0 = Base (QWERTY + number row, GACS home-row mods)
//         1 = Nav  (held via left thumb: arrows/editing/media)
//         2 = Sym  (held via right thumb: symbols, recovered keys)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
    //  outer --->                         <--- inner         inner --->                         <--- outer
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    
        LGUI_T(KC_A),LALT_T(KC_S),LCTL_T(KC_D),LSFT_T(KC_F),KC_G,             KC_H,    LSFT_T(KC_J),LCTL_T(KC_K),LALT_T(KC_L),LGUI_T(KC_SCLN),
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, 
    //  5th column bottom
                 KC_MINS, KC_EQL,                                               KC_LBRC, KC_RBRC, 
    //  thumb top
                                   LT(1, KC_SPC),KC_ESC,  ALL_T(KC_DEL),KC_DEL,  KC_ESC,  LT(2, KC_BSPC),
    //  thumb bottom
                                            KC_ENT,  KC_TAB,  KC_TAB,  KC_ENT
    ),

    [1] = LAYOUT(
    //  outer --->                         <--- inner         inner --->                         <--- outer
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
        XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,          KC_CUT,  KC_INS,  KC_UNDO, KC_AGIN, KC_DEL,  
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_MUTE,          KC_COPY, KC_LEFT, KC_UP,   KC_DOWN, KC_RIGHT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,          KC_PSTE, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  
    //  5th column bottom
                 XXXXXXX, XXXXXXX,                                              XXXXXXX, XXXXXXX, 
    //  thumb top
                                   _______, _______, _______, _______, _______, _______, 
    //  thumb bottom
                                            _______, _______, _______, _______
    ),

    [2] = LAYOUT(
    //  outer --->                         <--- inner         inner --->                         <--- outer
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, 
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, 
        KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_PIPE,          KC_GRV,  KC_QUOT, KC_DQUO, KC_PLUS, KC_UNDS, 
        KC_TILD, KC_BSLS, KC_LT,   KC_GT,   KC_SLSH,          _______, _______, _______, _______, _______, 
    //  5th column bottom
                 _______, _______,                                              _______, _______, 
    //  thumb top
                                   CW_TOGG, _______, _______, _______, _______, _______, 
    //  thumb bottom
                                            _______, _______, _______, _______
    )

};
