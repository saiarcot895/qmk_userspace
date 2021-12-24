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

#include QMK_KEYBOARD_H
#include "keymap_user.h"
#include "rgb_matrix_user.h"

typedef union {
    uint32_t raw;
    struct {
        uint8_t brightness:8;
    };
} user_config_t;

user_config_t user_config;
uint8_t current_game = GAME_NONE;

#ifdef VIA_ENABLE
enum keyboard_command_id {
  kb_disable_backlight = 0x80,
  kb_enable_backlight,
  kb_set_active_rgb,
  kb_set_screensaver_rgb,
  kb_game
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[MAC_BASE] = LAYOUT_ansi_82( 
     KC_ESC,             KC_BRID,  KC_BRIU,  KC_F3,    KC_F4,    RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,   KC_INS,
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
     KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
     KC_LCTL,  KC_LALT,  KC_LGUI,                                KC_SPC,                                 KC_RGUI, MO(MAC_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[MAC_FN] = LAYOUT_ansi_82( 
     KC_TRNS,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS, 
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[WIN_BASE] = LAYOUT_ansi_82( 
     KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_HOME,
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
     KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_END,
     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
     KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(WIN_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[WIN_FN] = LAYOUT_ansi_82( 
     KC_TRNS,            KC_BRID,  KC_BRIU,  KC_F23,   KC_F24,   RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,   KC_TRNS,
     KC_TRNS,  KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS, 
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS)

};

void eeconfig_init_user(void) {
    user_config.raw = 0;

    user_config.brightness = 128;
    eeconfig_update_user(user_config.raw);

    rgblight_enable();
    HSV current = rgb_matrix_get_hsv();
    rgb_matrix_sethsv_noeeprom(current.h, current.s, user_config.brightness);
}

void keyboard_post_init_user(void) {
    // Call the keymap level matrix init.
    debug_enable = true;

    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();

    HSV current = rgb_matrix_get_hsv();
    rgb_matrix_sethsv(current.h, current.s, user_config.brightness);
}

void matrix_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
        rgb_matrix_init_user();
#endif
}

static bool is_alt_tab_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LALT:
            if (record->event.pressed) {
                is_alt_tab_active = true;
            } else {
                is_alt_tab_active = false;
            }
            return true;
        case KC_F13:
        case KC_F14:
            if (record->event.pressed) {
                if (is_alt_tab_active) {
                    clear_keyboard();
                    keymap_config.nkro = false;
                    tap_code(KC_LCTL);
                    tap_code(KC_LCTL);
                    tap_code(keycode - KC_F13 + KC_1);
                    clear_keyboard();
                    keymap_config.nkro = true;
                }
            }
            return false;  // Skip all further processing of this key
        default:
            return true;  // Process all other keycodes normally
    }
}

#ifdef VIA_ENABLE

void raw_hid_receive_kb(uint8_t *data, uint8_t length)
{
    uint8_t *command_id = &(data[0]);
    uint8_t *command_data = &(data[1]);
    switch ( *command_id ) {
        case id_get_keyboard_value:
            {
                switch(command_data[0]) {
                    case kb_game:
                        {
                            command_data[1] = current_game;
                            break;
                        }
#if 0
                    case id_encoder_custom:
                        {
                            uint8_t custom_encoder_idx = command_data[1];
                            uint16_t keycode = retrieve_custom_encoder_config(custom_encoder_idx, ENC_CUSTOM_CW);
                            command_data[2] =  keycode >> 8;
                            command_data[3] = keycode & 0xFF;
                            keycode = retrieve_custom_encoder_config(custom_encoder_idx, ENC_CUSTOM_CCW);
                            command_data[4] =  keycode >> 8;
                            command_data[5] = keycode & 0xFF;
                            keycode = retrieve_custom_encoder_config(custom_encoder_idx, ENC_CUSTOM_PRESS);
                            command_data[6] =  keycode >> 8;
                            command_data[7] = keycode & 0xFF;
                            break;
                        }
#endif
                    default:
                        {
                            *command_id = id_unhandled;
                            break;
                        }
                }
                break;
            }
        case id_set_keyboard_value:
            {
                switch(command_data[0]) {
#ifdef RGB_MATRIX_ENABLE
                    case kb_disable_backlight:
                        {
                            rgb_matrix_disable_noeeprom();
                            break;
                        }
                    case kb_enable_backlight:
                        {
                            rgb_matrix_enable_noeeprom();
                            break;
                        }
                    case kb_set_active_rgb:
                        {
                            rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
                            break;
                        }
                    case kb_set_screensaver_rgb:
                        {
                            rgb_matrix_mode_noeeprom(RGB_MATRIX_DIGITAL_RAIN);
                            break;
                        }
                    case kb_game:
                        {
                            uint8_t new_game = command_data[1];
                            if (new_game >= GAME_NONE && new_game <= MAX_GAME_VALUE) {
                                current_game = new_game;
                            }
                            break;
                        }
#endif
#if 0
                    case id_encoder_custom:
                        {
                            uint8_t custom_encoder_idx = command_data[1];
                            uint8_t encoder_behavior = command_data[2];
                            uint16_t keycode = (command_data[3] << 8) | command_data[4];
                            set_custom_encoder_config(custom_encoder_idx, encoder_behavior, keycode);
                            break;
                        }
#endif
                    default:
                        {
                            *command_id = id_unhandled;
                            break;
                        }
                }
                break;
            }
        default:
            {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
    }
    // DO NOT call raw_hid_send(data,length) here, let caller do this
}
#endif
