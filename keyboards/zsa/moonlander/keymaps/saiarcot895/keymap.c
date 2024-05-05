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

static bool prev_transport_connected = true;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
#ifdef TWITCH_EMOTES
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    TO(EMOTE_SOURCE), XXXXXXX,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
#else
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    TO(MODTAP),   TO(MODTAP),  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
#endif
        KC_DEL,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    TG(FUNCTION), TG(FUNCTION), KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HYPR,           KC_MEH,  KC_H,    KC_J,    KC_K,    KC_L,    LT(MOUSE, KC_SCLN), KC_QUOT,
        KC_LSFT, LCTL_T(KC_Z),KC_X,KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  RCTL_T(KC_SLSH), KC_RSFT,
    LT(FUNCTION,KC_GRV),KC_NO,XXXXXXX,KC_LEFT, KC_RGHT,  KC_LALT,         RCTL_T(KC_ESC), KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, MO(FUNCTION),
                                            KC_SPC,  KC_BSPC, KC_LGUI,           KC_LALT, KC_TAB,  KC_ENT
    ),

    [MODTAP] = LAYOUT(
#ifdef TWITCH_EMOTES
        KC_EQL,  KC_1,        KC_2,        KC_3,        KC_4,  KC_5,    TO(EMOTE_SOURCE), XXXXXXX,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
#else
        KC_EQL,  KC_1,        KC_2,        KC_3,        KC_4,  KC_5,    TO(BASE),        TO(BASE),  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
#endif
        KC_DEL,  KC_Q,        KC_W,        KC_E,        KC_R,  KC_T,    TG(FUNCTION), TG(FUNCTION), KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_BSPC, KC_A, LALT_T(KC_S),LSFT_T(KC_D),LCTL_T(KC_F), KC_G,    KC_HYPR,           KC_MEH,  KC_H,RCTL_T(KC_J),RSFT_T(KC_K),RALT_T(KC_L),LT(MOUSE, KC_SCLN), KC_QUOT,
        KC_LSFT, KC_Z,        KC_X,        KC_C,        KC_V,  KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  RCTL_T(KC_SLSH), KC_RSFT,
    LT(FUNCTION,KC_GRV),KC_NO,XXXXXXX,KC_LEFT, KC_RGHT,  KC_LALT,         RCTL_T(KC_ESC), KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, MO(FUNCTION),
                                            KC_SPC,  KC_BSPC, KC_LGUI,           KC_LALT, KC_TAB,  KC_ENT
    ),

    [FUNCTION] = LAYOUT(
        DISPLAY_1, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,           _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        DISPLAY_2, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,           _______, KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, KC_F12,
        _______, KC_LPRN, KC_RPRN, _______, _______, KC_GRV,  _______,           _______, _______, KC_UP,   _______, _______, _______, _______,
        _______, KC_LBRC, KC_RBRC, _______, _______, KC_TILD,                             KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,           _______,          _______, KC_DOT,  _______, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),

    [MOUSE] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,
        XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, KC_MPLY, KC_MPRV, KC_MNXT, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_BTN1,           KC_BTN2,          KC_VOLU, KC_VOLD, KC_MUTE, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX
    ),

#ifdef TWITCH_EMOTES
    [EMOTE_SOURCE] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(EMOTES_PCROW), XXXXXXX,
        XXXXXXX, TO(EMOTES_ALANA), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(EMOTES_LIVHAR), XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(EMOTES_BTTV),                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   TO(LINUX_BASE),    TO(LINUX_BASE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [EMOTES_ALANA] = LAYOUT(
        XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,           XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ALANA_AVO_GROOVE, XXXXXXX,  XXXXXXX, ALANA_HI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, ALANA_CLAP, ALANA_GOODVIBES, XXXXXXX,                             XXXXXXX, ALANA_MUSHROOM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   TO(LINUX_BASE),    TO(LINUX_BASE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [EMOTES_BTTV] = LAYOUT(
        XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,           XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BTTV_PUG, XXXXXXX,
        XXXXXXX, XXXXXXX, BTTV_SWAY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, BTTV_CAT, XXXXXXX, BTTV_LETSGO, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, BTTV_PEEPOCLAP, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   TO(LINUX_BASE),    TO(LINUX_BASE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [EMOTES_LIVHAR] = LAYOUT(
        XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,           XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, LIVHAR_DANCE, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LIVHAR_LIGHT, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, LIVHAR_CLAP, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   TO(LINUX_BASE),    TO(LINUX_BASE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [EMOTES_PCROW] = LAYOUT(
        XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,           XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, PCROW_BOUNCE,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   TO(LINUX_BASE),    TO(LINUX_BASE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX
    ),
#endif

    [FORTNITE] = LAYOUT(
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_M,          XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_DEL,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_I,          XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_ESC,          XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LSFT, KC_M,    KC_I,    KC_C,    KC_V,    KC_B,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LCTL, KC_NO,XXXXXXX,KC_LEFT, KC_RGHT,  KC_LALT,                      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            KC_LCTL,  KC_SPC, KC_LGUI,          XXXXXXX,  XXXXXXX, XXXXXXX
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

#ifdef TWITCH_EMOTES
extern uint8_t emote_repeat_count;
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef TWITCH_EMOTES
    if (IS_LAYER_ON_STATE(state, EMOTE_SOURCE)) {
        emote_repeat_count = 1;
    }
#endif
    if (IS_LAYER_ON_STATE(state, MODTAP)) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_HUE_WAVE);
    } else {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
    }
    return state;
}

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

void housekeeping_task_user(void) {
    if (is_transport_connected() != prev_transport_connected) {
        if (is_transport_connected()) {
            layer_move(BASE);
        } else {
            layer_move(FORTNITE);
        }
        prev_transport_connected = is_transport_connected();
    }
}
