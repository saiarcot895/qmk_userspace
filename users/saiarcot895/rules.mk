RAW_ENABLE = yes
BOOTMAGIC_ENABLE := yes
LTO_ENABLE = yes
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
TWITCH_EMOTES_ENABLE = no

ifeq ($(strip $(TWITCH_EMOTES_ENABLE)), yes)
    OPT_DEFS += -DTWITCH_EMOTES
endif

SRC += user_keymap.c

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    SRC += rgb_matrix_user.c
endif
