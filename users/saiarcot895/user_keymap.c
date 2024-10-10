#include QMK_KEYBOARD_H
#include <via.h>
#include <raw_hid.h>
#include "action_layer.h"
#include "user_keymap.h"
#include "rgb_matrix_user.h"
#include "sm_td/sm_td.h"

user_config_t user_config;
uint8_t current_game = GAME_NONE;
#ifdef TWITCH_EMOTES
static uint8_t emote_repeat_count = 0;
#endif
static uint8_t modtap_mode = 0;

enum keyboard_command_id {
  kb_enable_backlight,
  kb_rgb_mode,
  kb_rgb_speed,
  kb_game,
};

enum rgb_modes {
    computer_active = 0x0,
    computer_locked,
    computer_screensaver,
};


void eeconfig_init_user(void) {
    user_config.raw = 0;

    user_config.brightness = 128;
    user_config.layer = BASE;
    eeconfig_update_user(user_config.raw);

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable();
    HSV current = rgb_matrix_get_hsv();
    rgb_matrix_sethsv_noeeprom(current.h, current.s, user_config.brightness);
#endif
    layer_move(user_config.layer);
}

void emotes_finished(tap_dance_state_t *state, void *user_data) {
#ifdef TWITCH_EMOTES
    if (state->count == 2) {
        layer_move(EMOTE_SOURCE);
    } else if (state->count == 3) {
        if (IS_LAYER_ON(MODTAP)) {
            layer_move(BASE);
        } else {
            layer_move(MODTAP);
        }
    } else if (state->count == 4) {
        layer_move(MOUSE);
    }
#else
    if (state->count == 2) {
        if (IS_LAYER_ON(MODTAP)) {
            layer_move(BASE);
        } else {
            layer_move(MODTAP);
        }
    } else if (state->count == 3) {
        layer_move(MOUSE);
    }
#endif
}

static void set_keyboard_mode_color_scheme(void) {
    if (modtap_mode) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_HUE_BREATHING);
        rgb_matrix_sethsv_noeeprom(180, 255, 128);
    } else {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef TWITCH_EMOTES
    if (IS_LAYER_ON_STATE(state, EMOTE_SOURCE)) {
        emote_repeat_count = 1;
    }
#endif
    if (IS_LAYER_ON_STATE(state, MODTAP)) {
        modtap_mode = 1;
    } else {
        modtap_mode = 0;
    }
    set_keyboard_mode_color_scheme();
    return state;
}

#ifdef TWITCH_EMOTES
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
        for (uint8_t i = 1; i < emote_repeat_count; i++) {
            tap_code(KC_V);
        }
        clear_keyboard();
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        return false;
    }

#ifdef TWITCH_EMOTES
    uint8_t current_layer = 0;
#endif
    switch (keycode) {
        case DISPLAY_1:
        case DISPLAY_2:
            if (record->event.pressed) {
                clear_keyboard();
                keymap_config.nkro = false;
                tap_code(KC_LCTL);
                tap_code(KC_LCTL);
                tap_code(keycode - DISPLAY_1 + KC_1);
                clear_keyboard();
                keymap_config.nkro = true;
                eeconfig_update_user(user_config.raw);
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
#ifdef TWITCH_EMOTES
        case KC_1:
        case KC_2:
        case KC_3:
        case KC_4:
        case KC_5:
        case KC_6:
        case KC_7:
        case KC_8:
        case KC_9:
        case KC_0:
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
#endif
        default:
            return true;  // Process all other keycodes normally
    }
}

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(CKC_S, KC_S, KC_LEFT_ALT)
        SMTD_MT(CKC_D, KC_D, KC_LSFT)
        SMTD_MT(CKC_F, KC_F, KC_LEFT_CTRL)
        SMTD_MT(CKC_J, KC_J, KC_RIGHT_CTRL)
        SMTD_MT(CKC_K, KC_K, KC_RSFT)
        SMTD_MT(CKC_L, KC_L, KC_RIGHT_ALT)
    }
}

#ifdef RAW_ENABLE
#ifdef VIA_ENABLE
void via_custom_value_command_kb(uint8_t *data, uint8_t length)
#else
void raw_hid_receive(uint8_t *data, uint8_t length)
#endif
{
    uint8_t *command_id = &(data[0]);
    uint8_t *command_data = &(data[1]);
    switch ( *command_id ) {
        case id_custom_get_value:
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
                            if (mode == RGB_MATRIX_CUSTOM_CUSTOM_DIGITAL_RAIN) {
                                command_data[1] = computer_locked;
                            } else {
                                command_data[1] = computer_active;
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
        case id_custom_set_value:
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
                                set_keyboard_mode_color_scheme();
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
