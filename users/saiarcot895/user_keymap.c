#include <rgb_matrix.h>
#include <raw_hid.h>
#include <via.h>
#include "user_keymap.h"
#include "rgb_matrix_user.h"

user_config_t user_config;
uint8_t current_game = GAME_NONE;
static uint8_t emote_repeat_count = 0;

enum keyboard_command_id {
  kb_enable_backlight = 0x80,
  kb_rgb_mode,
  kb_rgb_speed,
  kb_game,
};

enum rgb_modes {
    computer_active = 0x0,
    computer_locked,
    computer_screensaver,
};

static void emotes_finished(qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_EMOTES] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, emotes_finished, NULL),
};

void eeconfig_init_user(void) {
    user_config.raw = 0;

    user_config.brightness = 128;
    user_config.layer = LINUX_BASE;
    eeconfig_update_user(user_config.raw);

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable();
    HSV current = rgb_matrix_get_hsv();
    rgb_matrix_sethsv_noeeprom(current.h, current.s, user_config.brightness);
#endif
    layer_move(user_config.layer);
}

static void emotes_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        layer_move(EMOTE_SOURCE);
        emote_repeat_count = 1;
    }
}

static void send_emote(uint16_t keycode) {
    const char *emote = NULL;
    bool isBttv = false;
    switch (keycode) {
        case ALANA_CLAP:
            emote = PSTR("alanab3Clap ");
            break;
        case ALANA_MUSHROOM:
            emote = PSTR("alanab3Mushroom ");
            break;
        case ALANA_AVO_GROOVE:
            emote = PSTR("alanab3AvoGroove ");
            break;
        case ALANA_HI:
            emote = PSTR("alanab3MushHi ");
            break;
        case ALANA_GOODVIBES:
            emote = PSTR("alanab3GOODvIBES ");
            break;
        case BTTV_PEEPOCLAP:
            emote = PSTR("PeepoClap ");
            isBttv = true;
            break;
        case BTTV_LETSGO:
            emote = PSTR("LETSGO ");
            isBttv = true;
            break;
        case BTTV_PUG:
            emote = PSTR("pugPls ");
            isBttv = true;
            break;
        case BTTV_CAT:
            emote = PSTR("catJAM ");
            isBttv = true;
            break;
        case BTTV_SWAY:
            emote = PSTR("haseSlow ");
            isBttv = true;
            break;
        case PCROW_BOUNCE:
            emote = PSTR("pcrowBounce ");
            break;
        case PCROW_BED:
            emote = PSTR("pcrowBed ");
            break;
        case LIVHAR_CLAP:
            emote = PSTR("livharClapping ");
            break;
        case LIVHAR_DANCE:
            emote = PSTR("livharDanceparty ");
            break;
        case LIVHAR_LIGHT:
            emote = PSTR("livharLightSway ");
            break;
        default:
            layer_move(LINUX_BASE);
            return;
    }

    send_string_P(emote);
    layer_move(LINUX_BASE);

    if (emote_repeat_count > 1) {
        if (isBttv) {
            int emoteLen = strlen_P(emote);
            register_mods(MOD_BIT(KC_LSFT));
            for (int i = 0; i < emoteLen; i++) {
                tap_code(KC_LEFT);
            }
        } else {
            register_mods(MOD_BIT(KC_LSFT));
            tap_code(KC_LEFT);
            tap_code(KC_LEFT);
        }
        unregister_mods(MOD_BIT(KC_LSFT));
        register_mods(MOD_BIT(KC_LCTL));
        tap_code(KC_C);
        unregister_mods(MOD_BIT(KC_LCTL));
        tap_code(KC_RIGHT);
        register_mods(MOD_BIT(KC_LCTL));
        for (int i = 1; i < emote_repeat_count; i++) {
            tap_code(KC_V);
        }
        clear_keyboard();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t current_layer = 0;
    switch (keycode) {
        case KC_F13:
        case KC_F14:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_ALT) {
                    clear_keyboard();
                    keymap_config.nkro = false;
                    tap_code(KC_LCTL);
                    tap_code(KC_LCTL);
                    tap_code(keycode - KC_F13 + KC_1);
                    clear_keyboard();
                    keymap_config.nkro = true;
#if 0
                    if (keycode == KC_F13) {
                        user_config.layer = LINUX_BASE;
                    } else {
                        user_config.layer = WIN_BASE;
                    }
                    layer_move(user_config.layer);
#endif
                    eeconfig_update_user(user_config.raw);
                }
            }
            return false;  // Skip all further processing of this key
        case RST_DE:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                SEND_STRING(SS_DELAY(500));
                SEND_STRING("killall plasmashell" SS_DELAY(500) SS_TAP(X_ENTER));
                SEND_STRING(SS_DELAY(1000));
                SEND_STRING(SS_LALT(SS_TAP(X_SPACE)));
                SEND_STRING(SS_DELAY(500));
                SEND_STRING("plasmashell" SS_DELAY(500) SS_TAP(X_ENTER));
            }
            return false;  // Skip all further processing of this key
        case WORDLE:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_LGUI));
                SEND_STRING(SS_DELAY(750));
                SEND_STRING("Chromium" SS_DELAY(300) SS_TAP(X_ENTER));
                SEND_STRING(SS_DELAY(1500));
                SEND_STRING("https://www.nytimes.com/games/wordle/index.html" SS_TAP(X_ENTER));
                SEND_STRING(SS_LCTL(SS_TAP(X_T)));
                SEND_STRING(SS_DELAY(1000));
                SEND_STRING("https://www.quordle.com/" SS_TAP(X_ENTER));
                SEND_STRING(SS_LCTL(SS_TAP(X_T)));
                SEND_STRING(SS_DELAY(1000));
                SEND_STRING("https://wafflegame.net/" SS_TAP(X_ENTER));
                SEND_STRING(SS_LCTL(SS_TAP(X_T)));
                SEND_STRING(SS_DELAY(1000));
                SEND_STRING("https://discord.com/channels/721037447382696050/937596273199030323" SS_TAP(X_ENTER));
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_TAB))) SS_DELAY(150));
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_TAB))) SS_DELAY(150));
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_TAB))) SS_DELAY(150));
                SEND_STRING("homie" SS_TAP(X_ENTER));
                SEND_STRING(SS_DELAY(100));
                SEND_STRING(SS_LCTL(SS_TAP(X_TAB)) SS_DELAY(150));
                SEND_STRING("homie" SS_TAP(X_ENTER));
                SEND_STRING(SS_DELAY(200));
                SEND_STRING("tunas" SS_TAP(X_ENTER));
                SEND_STRING(SS_DELAY(200));
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_TAB))) SS_DELAY(150));
                SEND_STRING(SS_DELAY(500));
                SEND_STRING("tunas" SS_TAP(X_ENTER));
            }
            return false;  // Skip all further processing of this key
        case KC_1:
        case KC_2:
        case KC_3:
        case KC_4:
        case KC_5:
        case KC_6:
        case KC_7:
        case KC_8:
        case KC_9:
            current_layer = get_highest_layer(layer_state);
            if (current_layer <= EMOTE_SOURCE) {
                return true;
            }
            if (!record->event.pressed) {
                emote_repeat_count = emote_repeat_count * 10 + keycode - KC_0;
            }
            return false;
        case ALANA_CLAP:
        case ALANA_MUSHROOM:
        case ALANA_AVO_GROOVE:
        case ALANA_HI:
        case ALANA_GOODVIBES:
        case BTTV_LETSGO:
        case BTTV_PEEPOCLAP:
        case BTTV_PUG:
        case BTTV_CAT:
        case BTTV_SWAY:
        case PCROW_BOUNCE:
        case PCROW_BED:
        case LIVHAR_CLAP:
        case LIVHAR_DANCE:
        case LIVHAR_LIGHT:
            if (!record->event.pressed) {
                send_emote(keycode);
            }
            return false;
        default:
            return true;  // Process all other keycodes normally
    }
}

#ifdef RAW_ENABLE
#ifdef VIA_ENABLE
void raw_hid_receive_kb(uint8_t *data, uint8_t length)
#else
void raw_hid_receive(uint8_t *data, uint8_t length)
#endif
{
    uint8_t *command_id = &(data[0]);
    uint8_t *command_data = &(data[1]);
    switch ( *command_id ) {
        case id_get_keyboard_value:
            {
                switch(command_data[0]) {
#ifdef RGB_MATRIX_ENABLE
                    case kb_enable_backlight:
                        {
                            command_data[1] = rgb_matrix_is_enabled();
                            break;
                        }
                    case kb_rgb_mode:
                        {
                            uint8_t mode = rgb_matrix_get_mode();
                            if (mode == RGB_MATRIX_RAINBOW_MOVING_CHEVRON) {
                                command_data[1] = computer_active;
                            } else if (mode == RGB_MATRIX_CUSTOM_CUSTOM_DIGITAL_RAIN) {
                                command_data[1] = computer_locked;
                            }
                            break;
                        }
                    case kb_rgb_speed:
                        {
                            command_data[1] = rgb_matrix_get_speed();
                            break;
                        }
                    case kb_game:
                        {
                            command_data[1] = current_game;
                            break;
                        }
#endif
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
                    case kb_enable_backlight:
                        {
                            bool enabled = command_data[1];
                            if (enabled) {
                                rgb_matrix_enable_noeeprom();
                            } else {
                                rgb_matrix_disable_noeeprom();
                            }
                            break;
                        }
                    case kb_rgb_mode:
                        {
                            enum rgb_modes rgb_mode = command_data[1];
                            if (rgb_mode == computer_active) {
                                rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
                                rgb_matrix_set_speed_noeeprom(128);
                            } else if (rgb_mode == computer_locked || rgb_mode == computer_screensaver) {
                                rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_CUSTOM_DIGITAL_RAIN);
                            }
                            break;
                        }
                    case kb_rgb_speed:
                        {
                            uint8_t new_speed = command_data[1];
                            rgb_matrix_set_speed_noeeprom(new_speed);
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
#ifndef VIA_ENABLE
    raw_hid_send(data, length);
#endif
}
#endif
