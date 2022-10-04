#include QMK_KEYBOARD_H
#include "defines_danish.h"


// Define keymap layers
enum layers {
    _BASE,
    _RAISE,
    _LOWER,
    _FN
};

// Define custom keycodes
enum keycodes {
    // keys that differ between Mac and PC
    // keycodes defined in defines_danish.h
    CX_AT = SAFE_RANGE,
    CX_DLR,
    CX_BSLS,
    CX_PIPE,
    CX_LCBR,
    CX_RCBR,
    CX_PND,
    CX_EURO,

    CX_UNDO,
    CX_CUT,
    CX_COPY,
    CX_PSTE,

    OSTG,  // Toggle OS layout
    NEW_SAFE_RANGE
};


// User config 
typedef union {
    uint32_t raw;
    struct {
        bool macos :1;
    };
} user_config_t;
user_config_t user_config;


// Init user settings
void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user(); // Read config from EEPROM
    #ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
    #endif
};


// Create keymap LAYOUT_ortho_4x12 og LAYOUT_bov48 ????







// This is a hack to match US keycap legends on a Danish keyboard layout - using Key Override
const key_override_t shift_comm_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, DK_LABK);
const key_override_t shift_dot_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, DK_RABK);
const key_override_t shift_quot_key_override = ko_make_basic(MOD_MASK_SHIFT, DK_QUOT, DK_DQUO);
const key_override_t shift_scln_key_override = ko_make_basic(MOD_MASK_SHIFT, DK_SCLN, DK_COLN); 
const key_override_t shift_slsh_key_override = ko_make_basic(MOD_MASK_SHIFT, DK_SLSH, DK_QUES); 
//const key_override_t shift_bksp_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL); 

// Key Override array
const key_override_t **key_overrides = (const key_override_t *[]){
    &shift_comm_key_override,
    &shift_dot_key_override,
    &shift_quot_key_override,
    &shift_scln_key_override,
    &shift_slsh_key_override,
    //&shift_bksp_key_override,
    NULL
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        case OSTG: // OS toggle
            if (record->event.pressed) {
                user_config.macos ^= 1; // Toggles the status
                eeconfig_update_user(user_config.raw); // Writes to EEPROM!
            }
            return false;
        break;

        // Handle keycodes that differ between Mac and PC
        case CX_AT:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_AT : PC_AT);
            } else {
                unregister_code16((user_config.macos) ? MAC_AT : PC_AT);
            }
            return false;
        break;
        case CX_DLR:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_DLR : PC_DLR);
            } else {
                unregister_code16((user_config.macos) ? MAC_DLR : PC_DLR);
            }
            return false;
        break;
        case CX_BSLS:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_BSLS : PC_BSLS);
            } else {
                unregister_code16((user_config.macos) ? MAC_BSLS : PC_BSLS);
            }
            return false;
        break;
        case CX_PIPE:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_PIPE : PC_PIPE);
            } else {
                unregister_code16((user_config.macos) ? MAC_PIPE : PC_PIPE);
            }
            return false;
        break;
        case CX_LCBR:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_LCBR : PC_LCBR);
            } else {
                unregister_code16((user_config.macos) ? MAC_LCBR : PC_LCBR);
            }
            return false;
        break;
        case CX_RCBR:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_RCBR : PC_RCBR);
            } else {
                unregister_code16((user_config.macos) ? MAC_RCBR : PC_RCBR);
            }
            return false;
        break;
        case CX_PND:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_PND : PC_PND);
            } else {
                unregister_code16((user_config.macos) ? MAC_PND : PC_PND);
            }
            return false;
        break;
        case CX_EURO:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_EURO : PC_EURO);
            } else {
                unregister_code16((user_config.macos) ? MAC_EURO : PC_EURO);
            }
            return false;
        break;
        case CX_UNDO:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_UNDO : PC_UNDO);
            } else {
                unregister_code16((user_config.macos) ? MAC_UNDO : PC_UNDO);
            }
            return false;
        break;
        case CX_CUT:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_CUT : PC_CUT);
            } else {
                unregister_code16((user_config.macos) ? MAC_CUT : PC_CUT);
            }
            return false;
        break;
                case CX_COPY:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_COPY : PC_COPY);
            } else {
                unregister_code16((user_config.macos) ? MAC_COPY : PC_COPY);
            }
            return false;
        break;
                case CX_PSTE:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_PSTE : PC_PSTE);
            } else {
                unregister_code16((user_config.macos) ? MAC_PSTE : PC_PSTE);
            }
            return false;
        break;

    }

    return true;
}
