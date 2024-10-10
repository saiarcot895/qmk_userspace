/* Copyright 2022 @ Saikrishna Arcot
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

#pragma once

// clang-format off

enum layers {
    BASE,
    MODTAP,
    FUNCTION,
    MOUSE,
    FORTNITE,
#ifdef TWITCH_EMOTES
    EMOTE_SOURCE,
    EMOTES_BTTV,
    EMOTES_ALANA,
    EMOTES_PCROW,
    EMOTES_LIVHAR,
#endif
};

enum custom_keycodes {
    RST_DE = SAFE_RANGE,
    DISPLAY_1,
    DISPLAY_2,
#ifdef TWITCH_EMOTES
    ALANA_CLAP,
    ALANA_MUSHROOM,
    ALANA_AVO_GROOVE,
    ALANA_HI,
    ALANA_GOODVIBES,
    PCROW_BOUNCE,
    PCROW_BED,
    LIVHAR_CLAP,
    LIVHAR_DANCE,
    LIVHAR_LIGHT,
    BTTV_LETSGO,
    BTTV_PEEPOCLAP,
    BTTV_PUG,
    BTTV_CAT,
    BTTV_SWAY,
#endif
    SMTD_KEYCODES_BEGIN,
    CKC_S,
    CKC_D,
    CKC_F,
    CKC_J,
    CKC_K,
    CKC_L,
    SMTD_KEYCODES_END,
};

enum {
    TD_EMOTES,
};

typedef union {
    uint32_t raw;
    struct {
        uint8_t brightness:8;
        uint8_t layer:4;
    };
} user_config_t;

extern user_config_t user_config;
extern tap_dance_action_t tap_dance_actions[];

// clang-format on
