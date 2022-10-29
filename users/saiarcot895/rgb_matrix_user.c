/* Copyright 2021 @ Grayson Carr
 * Copyright 2022 @ Saikrishna Arcot
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
#include <rgb_matrix.h>
#include "rgb_matrix_user.h"
#include "user_keymap.h"

static keypos_t led_index_key_position[DRIVER_LED_TOTAL];

static bool is_not_drg_key(uint16_t keycode) {
    switch (keycode) {
        case KC_1:
        case KC_2:
        case KC_3:
        case KC_4:
        case KC_5:
        case KC_W:
        case KC_A:
        case KC_S:
        case KC_D:
        case KC_E:
        case KC_R:
        case KC_X:
        case KC_C:
        case KC_V:
        case KC_F:
        case KC_G:
        case KC_TAB:
        case KC_LSFT:
        case KC_LCTL:
        case KC_ESC:
            return false;
        default:
            return true;
    }
}

static bool is_not_dont_starve_key(uint16_t keycode) {
    switch (keycode) {
        case KC_W:
        case KC_A:
        case KC_S:
        case KC_D:
        case KC_Q:
        case KC_E:
        case KC_F:
        case KC_M:
        case KC_TAB:
        case KC_LSFT:
        case KC_LCTL:
        case KC_ESC:
        case KC_SPC:
            return false;
        default:
            return true;
    }
}

bool (*const game_rgb_mappings[MAX_GAME_VALUE])(uint16_t) = {
    [GAME_DRG] = is_not_drg_key,
    [GAME_DONT_STARVE] = is_not_dont_starve_key
};

void rgb_matrix_init_user(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led_index = g_led_config.matrix_co[row][col];
            if (led_index != NO_LED) {
                led_index_key_position[led_index] = (keypos_t){.row = row, .col = col};
            }
        }
    }
}

static bool is_caps_lock_indicator(uint16_t keycode) {
#ifdef CAPS_LOCK_INDICATOR_LIGHT_ALPHAS
    return (KC_A <= keycode && keycode <= KC_Z) || keycode == KC_CAPS;
#else
    return keycode == KC_CAPS;
#endif
}

static bool is_transparent(uint16_t keycode) { return keycode == KC_TRNS || keycode == KC_NO; }

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t current_layer = get_highest_layer(layer_state);
    switch (current_layer) {
        case LINUX_BASE:
        case WIN_BASE:
            if (current_game && current_game <= MAX_GAME_VALUE && game_rgb_mappings[current_game]) {
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, game_rgb_mappings[current_game], RGB_OFF);
                break;
            }
#ifdef CAPS_LOCK_INDICATOR_COLOR
            if (host_keyboard_led_state().caps_lock) {
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_caps_lock_indicator, CAPS_LOCK_INDICATOR_COLOR);
                break;
            }
#endif
            break;
        case LINUX_FN:
        case WIN_FN:
#ifdef FN_LAYER_TRANSPARENT_KEYS_OFF
            rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_transparent, RGB_OFF);
#endif
            break;
        default:
#ifdef FN_LAYER_TRANSPARENT_KEYS_OFF
            rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_transparent, RGB_OFF);
#endif
            break;
    }
}

void rgb_matrix_set_color_by_keycode(uint8_t led_min, uint8_t led_max, uint8_t layer, bool (*is_keycode)(uint16_t), uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = led_min; i < led_max; i++) {
        uint16_t keycode = keymap_key_to_keycode(layer, led_index_key_position[i]);
        if ((*is_keycode)(keycode)) {
            rgb_matrix_set_color(i, red, green, blue);
        }
    }
}
