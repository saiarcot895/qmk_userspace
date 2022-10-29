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
    LINUX_BASE,
    LINUX_FN,
    WIN_BASE,
    WIN_FN,
    EMOTE_SOURCE,
    EMOTES_BTTV,
    EMOTES_ALANA,
    EMOTES_PCROW,
    EMOTES_LIVHAR,
};

enum custom_keycodes {
    RST_DE = SAFE_RANGE,
    WORDLE,
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

// clang-format on
