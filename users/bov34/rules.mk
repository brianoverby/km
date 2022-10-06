# Fix after QMK Breaking Changes 2022 August 27: https://github.com/qmk/qmk_firmware/pull/17559/files
INTROSPECTION_KEYMAP_C = bov34.c
# File with keymap should not be in SRC
#SRC += bov34.c
SRC += oneshot.c


EXTRAKEY_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
TAP_DANCE_ENABLE = no
COMBO_ENABLE = no

MOUSEKEY_ENABLE = no
BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE = no
RGBLIGHT_ENABLE = no
LEADER_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
AUDIO_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no 
MAGIC_ENABLE = no

LTO_ENABLE = no
