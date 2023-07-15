/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#include "keycode.h"
#include QMK_KEYBOARD_H
#include "user_keymap.h"
#include "rgb_matrix_user.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LINUX_BASE] = LAYOUT_moonlander(
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LEFT,           KC_RGHT, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_DEL,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    TG(LINUX_FN), TG(LINUX_FN), KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HYPR,           KC_MEH,  KC_H,    KC_J,    KC_K,    KC_L,    LT(MOUSE, KC_SCLN), KC_QUOT,
        KC_LSFT, LCTL_T(KC_Z),KC_X,KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  RCTL_T(KC_SLSH), KC_RSFT,
    LT(LINUX_FN,KC_GRV),KC_NO,A(KC_LSFT),KC_LEFT, KC_RGHT,  KC_LALT,      RCTL_T(KC_ESC),  KC_UP,    KC_DOWN, KC_LBRC, KC_RBRC, MO(LINUX_FN),
                                            KC_SPC,  KC_BSPC, KC_LGUI,           KC_LALT,  KC_TAB,  KC_ENT
    ),

    [LINUX_FN] = LAYOUT_moonlander(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  _______,           _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,           _______, KC_CIRC, KC_AMPR, KC_ASTR, _______, KC_ASTR, KC_F12,
        _______, KC_LPRN, KC_RPRN, _______, _______, KC_GRV,  _______,           _______, _______, KC_UP,   _______, _______, KC_PLUS, _______,
        _______, KC_LBRC, KC_RBRC, _______, _______, KC_TILD,                             KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_BSLS, _______,
        _______, _______, _______, _______, _______,          _______,           _______,          _______, KC_DOT,  _______, KC_EQL,  _______,
                                            _______, _______, _______,           _______, _______, _______
    ),

    [MOUSE] = LAYOUT_moonlander(
        _______,  _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, QK_BOOT,
        _______, _______, _______, KC_MS_U, _______, _______, _______,           _______, _______, _______, _______, _______, _______, EE_CLR,
        _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,           _______, _______, _______, _______, _______, _______, KC_MPLY,
        _______, _______, _______, _______, _______, _______,                             _______, _______, KC_MPRV, KC_MNXT, _______, _______,
        _______, _______, _______, KC_BTN1, KC_BTN2,         _______,            _______,          KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),
};
// clang-format on

#if 0
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_KB_1:
            if (record->event.pressed) {
                keyboard_config.led_level ^= 1;
                eeconfig_update_kb(keyboard_config.raw);
                if (keyboard_config.led_level) {
                    layer_state_set_kb(layer_state);
                } else {
                    ML_LED_1(false);
                    ML_LED_2(false);
                    ML_LED_3(false);
                    ML_LED_4(false);
                    ML_LED_5(false);
                    ML_LED_6(false);
                }
            }
            break;
    }
    return true;
}
#endif

void keyboard_post_init_user(void) {
    // Call the keymap level matrix init.
    debug_enable = true;

    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();

    HSV current = rgb_matrix_get_hsv();
    rgb_matrix_sethsv(current.h, current.s, user_config.brightness);
    layer_move(user_config.layer);
}

void matrix_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_init_user();
#endif
}
