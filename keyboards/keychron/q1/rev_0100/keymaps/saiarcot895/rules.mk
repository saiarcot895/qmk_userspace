VIA_ENABLE = no
RAW_ENABLE = yes
BOOTMAGIC_ENABLE := yes
LTO_ENABLE = yes

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    SRC += rgb_matrix_user.c
endif
