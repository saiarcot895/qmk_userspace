RAW_ENABLE = yes
BOOTMAGIC_ENABLE := yes
LTO_ENABLE = yes
TAP_DANCE_ENABLE = yes

SRC += user_keymap.c

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    SRC += rgb_matrix_user.c
endif
