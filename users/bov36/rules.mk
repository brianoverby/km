# Fix after QMK Breaking Changes 2022 August 27: https://github.com/qmk/qmk_firmware/pull/17559/files
INTROSPECTION_KEYMAP_C = bov36.c

SRC += features/swapper.c
SRC += features/layer_lock.c

VPATH += keyboards/gboards

EXTRAKEY_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
COMBO_ENABLE = yes
MAGIC_ENABLE = yes
CAPS_WORD_ENABLE = yes

TAP_DANCE_ENABLE = no
BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE = no
RGBLIGHT_ENABLE = no
LEADER_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
AUDIO_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no 

LTO_ENABLE = no