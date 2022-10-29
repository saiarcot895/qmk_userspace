/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
#include "via.h"

static uint16_t quantum_scans = 0;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[LINUX_BASE] = LAYOUT_tkl_ansi( 
     KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,         KC_F11,       KC_F12,   KC_F13,   _______,  KC_PSCR,
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,        KC_EQL,       KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,        KC_RBRC,      KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
     KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                      KC_ENT,
     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                      KC_RSFT,            KC_UP,
     KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RGUI,  TD(TD_EMOTES),  MO(LINUX_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[LINUX_FN] = LAYOUT_tkl_ansi( 
     _______,            KC_BRID,  KC_BRIU,  KC_F23,   KC_F24,   _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,   RST_DE,  _______,
     _______,  KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   _______,  _______,    _______,  _______,  _______,  _______,
     _______,  _______,  WORDLE,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
     _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______, 
     _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),

[WIN_BASE] = LAYOUT_tkl_ansi( 
     KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,         KC_F11,       KC_F12,   KC_F13,   _______,  KC_PSCR,
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,        KC_EQL,       KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,        KC_RBRC,      KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
     KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                      KC_ENT,
     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                      KC_RSFT,            KC_UP,
     KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RGUI,  TD(TD_EMOTES),  MO(LINUX_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[WIN_FN] = LAYOUT_tkl_ansi( 
     _______,            KC_BRID,  KC_BRIU,  KC_F23,   KC_F24,   _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,   RST_DE,  _______,
     _______,  KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   _______,  _______,    _______,  _______,  _______,  _______,
     _______,  _______,  WORDLE,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
     _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______, 
     _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),

[EMOTE_SOURCE] = LAYOUT_tkl_ansi( 
     TO(LINUX_BASE),                     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,          XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,         XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,          XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,         XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,          XXXXXXX,  XXXXXXX,  XXXXXXX,            TO(EMOTES_PCROW),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,         TO(EMOTES_ALANA),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,          XXXXXXX,  XXXXXXX,  TO(EMOTES_LIVHAR),  XXXXXXX,           XXXXXXX,            XXXXXXX,
     XXXXXXX,                            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(EMOTES_BTTV),  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,           XXXXXXX,            XXXXXXX,            XXXXXXX, 
     XXXXXXX,         XXXXXXX,           XXXXXXX,                                XXXXXXX,                                                  XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),

[EMOTES_BTTV] = LAYOUT_tkl_ansi( 
     TO(LINUX_BASE),             XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,          XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,         KC_1,      KC_2,       KC_3,     KC_4,     KC_5,     KC_6,             KC_7,     KC_8,     KC_9,               KC_0,              XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,         XXXXXXX,   XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,          XXXXXXX,  XXXXXXX,  XXXXXXX,            BTTV_PUG,          XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,         XXXXXXX,   BTTV_SWAY,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,          BTTV_CAT, XXXXXXX,  BTTV_LETSGO,        XXXXXXX,           XXXXXXX,            XXXXXXX,
     XXXXXXX,                    XXXXXXX,    XXXXXXX,  BTTV_PEEPOCLAP,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,           XXXXXXX,            XXXXXXX,            XXXXXXX, 
     XXXXXXX,         XXXXXXX,   XXXXXXX,                                  XXXXXXX,                                                  XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),

[EMOTES_ALANA] = LAYOUT_tkl_ansi( 
     TO(LINUX_BASE),             XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,          XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,         KC_1,      KC_2,       KC_3,     KC_4,     KC_5,     KC_6,             KC_7,     KC_8,     KC_9,               KC_0,              XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,         XXXXXXX,   XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,          XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,         XXXXXXX,   XXXXXXX,    XXXXXXX,  XXXXXXX,  ALANA_AVO_GROOVE,  XXXXXXX,          XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,           XXXXXXX,            XXXXXXX,
     XXXXXXX,                    XXXXXXX,    XXXXXXX,  ALANA_CLAP, ALANA_GOODVIBES, XXXXXXX, XXXXXXX, ALANA_MUSHROOM,  XXXXXXX,            XXXXXXX,           XXXXXXX,            XXXXXXX,            XXXXXXX, 
     XXXXXXX,         XXXXXXX,   XXXXXXX,                                  XXXXXXX,                                                  XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),

[EMOTES_PCROW] = LAYOUT_tkl_ansi( 
     TO(LINUX_BASE),             XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,          XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,         KC_1,      KC_2,       KC_3,     KC_4,     KC_5,     KC_6,             KC_7,     KC_8,     KC_9,               KC_0,              XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,         XXXXXXX,   XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,          XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,         XXXXXXX,   PCROW_BED,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,          XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,           XXXXXXX,            XXXXXXX,
     XXXXXXX,                    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  PCROW_BOUNCE,     XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,           XXXXXXX,            XXXXXXX,            XXXXXXX, 
     XXXXXXX,         XXXXXXX,   XXXXXXX,                                  XXXXXXX,                                                  XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),

[EMOTES_LIVHAR] = LAYOUT_tkl_ansi( 
     TO(LINUX_BASE),             XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,          XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,         KC_1,      KC_2,       KC_3,     KC_4,     KC_5,     KC_6,             KC_7,     KC_8,     KC_9,               KC_0,              XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,         XXXXXXX,   XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,          XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
     XXXXXXX,         XXXXXXX,   XXXXXXX,    LIVHAR_DANCE,  XXXXXXX,  XXXXXXX,  XXXXXXX,          XXXXXXX,  XXXXXXX,  LIVHAR_LIGHT,            XXXXXXX,           XXXXXXX,            XXXXXXX,
     XXXXXXX,                    XXXXXXX,    XXXXXXX,  LIVHAR_CLAP,  XXXXXXX,  PCROW_BOUNCE,     XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,           XXXXXXX,            XXXXXXX,            XXXXXXX, 
     XXXXXXX,         XXXXXXX,   XXXXXXX,                                  XXXXXXX,                                                  XXXXXXX,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),

};

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

bool dip_switch_update_user(uint8_t index, bool active) {
    // Process this only after 500 scans, to ignore the initial
    // setting.
    if (quantum_scans >= 500) {
        // Allow the user to use the hardware switch, but suppress
        // default behavior
        user_config.layer = active ? WIN_BASE : LINUX_BASE;
        layer_move(user_config.layer);
        eeconfig_update_user(user_config.raw);
    }
    return false;
}

void matrix_scan_user(void) {
    if (quantum_scans < 750) {
        ++quantum_scans;
    }
}
