#include QMK_KEYBOARD_H
#include "features/oneshot.h"
#include "features/swapper.h"
#include "defines_danish.h"


// Define keymap layers
enum layers {
    _BASE,
    _NAV,
    _NUM,
    _SYM,
    _SYS
};

// Define custom keycodes
enum keycodes {
    // keys that differ between Mac and PC
    // keycodes defined in defines_danish.h
    AT = SAFE_RANGE,
    DLR,
    BSLS,
    PIPE,
    LCBR,
    RCBR,
    PND,
    EURO,

    UNDO,
    CUT,
    COPY,
    PSTE,

    LOCK,
    SW_WIN,

    OSTG,  // Toggle OS layout
    OSWIN,
    OSMAC,

    OS_SHFT,  // Oneshot keys
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    NEW_SAFE_RANGE
};

// Combos defined in combos.def
#if defined(COMBO_ENABLE)
#include "g/keymap_combo.h"
#endif


// One Shot Modifiers 
#define OSM_SFT OSM(MOD_LSFT)
// #define OS_CTRL OSM(MOD_LCTL)
// #define OS_ALT OSM(MOD_LALT)
// #define OS_CMD OSM(MOD_LGUI)


// Layer change
//#define LA_NAV TT(_NAV)
#define LA_NAV LT(_NAV,KC_SPC)
//#define LA_NUM TT(_NUM)
//#define LA_NAV LT(_NAV,KC_TAB)
#define LA_SYM LT(_SYM,KC_ENT)
#define LA_NUM LT(_NUM,KC_BSPC)

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
                                   LA_NAV,  OSM_SFT,                   LA_SYM,  LA_NUM   
    ),

    [_NAV] = LAYOUT_bov34(
        KC_ESC,  XXXXXXX, XXXXXXX, SW_WIN,  KC_VOLU,                   KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_VOLD,                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,
        UNDO,    CUT,     COPY,    PSTE,    LOCK,                      KC_TAB,  DK_AE,   DK_OE,   DK_AA,   XXXXXXX,
                                   _______, _______,                   _______, _______
    ),
    
    [_NUM] = LAYOUT_bov34(
        KC_F11,  KC_7,    KC_8,    KC_9,    DK_MINS,                   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
        KC_F12,  KC_4,    KC_5,    KC_6,    KC_COMM,                   XXXXXXX, OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
        KC_TAB,  KC_1,    KC_2,    KC_3,    KC_DOT,                    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                                   _______, KC_0,                      _______, _______
    ),

    [_SYM] = LAYOUT_bov34(
        DK_EXLM, AT,      DK_HASH, DLR,     DK_PERC,                   XXXXXXX, DK_LPRN, DK_RPRN, DK_CIRC, DK_TILD,
        DK_AMPR, DK_ASTR, DK_UNDS, DK_QUOT, DK_DQUO,                   XXXXXXX, LCBR,    RCBR,    DK_ACUT, DK_GRV,
        PIPE,    DK_PLUS, DK_MINS, DK_EQL,  BSLS,                      XXXXXXX, DK_LBRC, DK_RBRC, DK_DIAE, XXXXXXX,
                                   _______, XXXXXXX,                   _______, _______
    ),

    [_SYS] = LAYOUT_bov34(
        XXXXXXX, OSWIN,   XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, OSMAC,   XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, XXXXXXX,                   XXXXXXX, _______
    )

};


// This is a hack to match US keycap legends on a Danish keyboard layout - using Key Override
const key_override_t shift_comm_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, DK_LABK);
const key_override_t shift_dot_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, DK_RABK);
const key_override_t shift_quot_key_override = ko_make_basic(MOD_MASK_SHIFT, DK_QUOT, DK_DQUO);
const key_override_t shift_scln_key_override = ko_make_basic(MOD_MASK_SHIFT, DK_SCLN, DK_COLN); 
const key_override_t shift_slsh_key_override = ko_make_basic(MOD_MASK_SHIFT, DK_SLSH, DK_QUES); 

// Key Override array
const key_override_t **key_overrides = (const key_override_t *[]){
    &shift_comm_key_override,
    &shift_dot_key_override,
    &shift_quot_key_override,
    &shift_scln_key_override,
    &shift_slsh_key_override,
    NULL
};


// Callum oneshot
bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case LA_NAV:
        case LA_NUM:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LA_NAV:
        case LA_NUM:
        case LA_SYM:
        case OSM_SFT:
        case KC_LSFT:
        case OS_SHFT:
        case OS_CTRL:
        case OS_ALT:
        case OS_CMD:
            return true;
        default:
            return false;
    }
}

bool sw_win_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;



layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NAV, _NUM, _SYS);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // Check for Windows or macOS before updating swapper
    uint16_t WINSW_KEY = (user_config.macos) ? KC_LCMD : KC_LALT;

    update_swapper(
            &sw_win_active, WINSW_KEY, KC_TAB, SW_WIN,
            keycode, record
        );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    switch (keycode) {

        case OSTG: // OS toggle
            if (record->event.pressed) {
                user_config.macos ^= 1; // Toggles the status
                eeconfig_update_user(user_config.raw); // Writes to EEPROM!
            }
            return false;
        break;
        case OSWIN: // Windows
            if (record->event.pressed) {
                user_config.macos = 0; 
                eeconfig_update_user(user_config.raw); // Writes to EEPROM!
            }
            return false;
        break;
        case OSMAC: // macOS
            if (record->event.pressed) {
                user_config.macos = 1;
                eeconfig_update_user(user_config.raw); // Writes to EEPROM!
            }
            return false;
        break;

        // Handle keycodes that differ between Mac and PC
        case AT:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_AT : PC_AT);
            } else {
                unregister_code16((user_config.macos) ? MAC_AT : PC_AT);
            }
            return false;
        break;
        case DLR:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_DLR : PC_DLR);
            } else {
                unregister_code16((user_config.macos) ? MAC_DLR : PC_DLR);
            }
            return false;
        break;
        case BSLS:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_BSLS : PC_BSLS);
            } else {
                unregister_code16((user_config.macos) ? MAC_BSLS : PC_BSLS);
            }
            return false;
        break;
        case PIPE:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_PIPE : PC_PIPE);
            } else {
                unregister_code16((user_config.macos) ? MAC_PIPE : PC_PIPE);
            }
            return false;
        break;
        case LCBR:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_LCBR : PC_LCBR);
            } else {
                unregister_code16((user_config.macos) ? MAC_LCBR : PC_LCBR);
            }
            return false;
        break;
        case RCBR:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_RCBR : PC_RCBR);
            } else {
                unregister_code16((user_config.macos) ? MAC_RCBR : PC_RCBR);
            }
            return false;
        break;
        case PND:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_PND : PC_PND);
            } else {
                unregister_code16((user_config.macos) ? MAC_PND : PC_PND);
            }
            return false;
        break;
        case EURO:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_EURO : PC_EURO);
            } else {
                unregister_code16((user_config.macos) ? MAC_EURO : PC_EURO);
            }
            return false;
        break;
        case UNDO:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_UNDO : PC_UNDO);
            } else {
                unregister_code16((user_config.macos) ? MAC_UNDO : PC_UNDO);
            }
            return false;
        break;
        case CUT:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_CUT : PC_CUT);
            } else {
                unregister_code16((user_config.macos) ? MAC_CUT : PC_CUT);
            }
            return false;
        break;
        case COPY:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_COPY : PC_COPY);
            } else {
                unregister_code16((user_config.macos) ? MAC_COPY : PC_COPY);
            }
            return false;
        break;
        case PSTE:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_PSTE : PC_PSTE);
            } else {
                unregister_code16((user_config.macos) ? MAC_PSTE : PC_PSTE);
            }
            return false;
        break;
        case LOCK:
            if(record->event.pressed) {
                register_code16((user_config.macos) ? MAC_LOCK : PC_LOCK);
            } else {
                unregister_code16((user_config.macos) ? MAC_LOCK : PC_LOCK);
            }
            return false;
        break;

    }

    return true;
}
