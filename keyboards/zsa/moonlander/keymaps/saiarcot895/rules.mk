AUDIO_ENABLE = no

ifeq ($(strip $(TWITCH_EMOTES_ENABLE)), yes)
    VIA_ENABLE = no
else
    VIA_ENABLE = yes
endif
