#include QMK_KEYBOARD_H
#include "defines_danish.h"

// Define keymap layers
enum layers {
    _BASE,
    _SYM,
    _NAV,
    _NUM
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


// One Shot Modifiers 
#define OS_SHFT OSM(MOD_LSFT)
#define OS_CTRL OSM(MOD_LCTL)
#define OS_ALT OSM(MOD_LALT)
#define OS_CMD OSM(MOD_LGUI)


// Layer change
#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)


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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_bov34(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    DK_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  DK_SLSH,
                                   LA_NAV,  OS_SHFT,                   KC_SPC,  LA_SYM   
    ),

    [_SYM] = LAYOUT_bov34(
        DK_EXLM, CX_AT,   DK_HASH, CX_DLR,  DK_LPRN,                   DK_RPRN, DK_AMPR, DK_GRV,  DK_CIRC, DK_PERC,
        DK_TILD, DK_UNDS, CX_PIPE, CX_BSLS, CX_LCBR,                   CX_RCBR, XXXXXXX, DK_ACUT, DK_QUOT, DK_DQUO,
        DK_PLUS, DK_MINS, DK_ASTR, DK_EQL,  DK_LBRC,                   DK_RBRC, DK_DIAE, DK_AE,   DK_OE,   DK_AA,
                                   _______, _______,                   _______, _______
    ),

    [_NAV] = LAYOUT_bov34(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_TAB,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSPC,
        CX_UNDO, CX_CUT,  CX_COPY, CX_PSTE, KC_ESC,                    KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_ENT,
                                   _______, _______,                   _______, _______
    ),
    
    [_NUM] = LAYOUT_bov34(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,                   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_VOLD,                   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        OSTG,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______,                   _______, _______
    )

};


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


layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}