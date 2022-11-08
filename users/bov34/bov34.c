#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "defines_danish.h"


// Define keymap layers
enum layers {
    _BASE,
    _NAV,
    _NUM,
    _SYM
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

    CX_LOCK,

    OSTG,  // Toggle OS layout

    OS_SHFT,  // Oneshot keys
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    OS_CNCL,

    RPT,   // Repeat key

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
#define LA_NAV TT(_NAV)
#define LA_NUM TT(_NUM)


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
                                   LA_NAV,  KC_SPC,                    OSM_SFT, LA_NUM   
    ),

    [_NAV] = LAYOUT_bov34(
        KC_ESC,  XXXXXXX, XXXXXXX, RPT,     KC_VOLU,                   KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_BSPC,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_VOLD,                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,
        CX_UNDO, CX_CUT,  CX_COPY, CX_PSTE, CX_LOCK,                   KC_TAB,  DK_AE,   DK_OE,   DK_AA,   XXXXXXX,
                                   _______, XXXXXXX,                   KC_BSPC, _______
    ),
    
    [_NUM] = LAYOUT_bov34(
        KC_F11,  KC_7,    KC_8,    KC_9,    DK_MINS,                   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
        KC_F12,  KC_4,    KC_5,    KC_6,    KC_COMM,                   XXXXXXX, OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
        KC_TAB,  KC_1,    KC_2,    KC_3,    KC_DOT,                    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                                   _______, KC_0,                      XXXXXXX, _______
    ),

    [_SYM] = LAYOUT_bov34(
        DK_EXLM, CX_AT,   DK_HASH, CX_DLR,  DK_PERC,                   XXXXXXX, DK_LPRN, DK_RPRN, DK_CIRC, DK_TILD,
        DK_AMPR, DK_ASTR, DK_UNDS, DK_QUOT, DK_DQUO,                   XXXXXXX, CX_LCBR, CX_RCBR, DK_ACUT, DK_GRV,
        CX_PIPE, DK_PLUS, DK_MINS, DK_EQL,  CX_BSLS,                   XXXXXXX, DK_LBRC, DK_RBRC, DK_DIAE, XXXXXXX,
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

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;


// Repeat key implementation
// https://gist.github.com/NotGate/3e3d8ab81300a86522b2c2549f99b131?permalink_comment_id=4282534#gistcomment-4282534

// Used to extract the basic tapping keycode from a dual-role key.
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
uint16_t last_keycode = KC_NO;
uint8_t last_modifier = 0;
uint16_t pressed_keycode = KC_NO;


void process_repeat_key(uint16_t keycode, const keyrecord_t *record) {
  if (keycode != RPT) {
    // Early return when holding down a pure layer key
    // to retain modifiers
    switch (keycode) {
      case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
      case QK_MOMENTARY ... QK_MOMENTARY_MAX:
      case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
      case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
      case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
      case QK_TO ... QK_TO_MAX:
      case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
      case QK_MODS ... QK_MODS_MAX:
        return;
    }
    if (record->event.pressed) {
      last_modifier = get_mods() | get_oneshot_mods();
      switch (keycode) {
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
          last_keycode = GET_TAP_KC(keycode);
          break;
        default:
          last_keycode = keycode;
          break;
        }
    }
  } else { // keycode == RPT
    if (record->event.pressed) {
      pressed_keycode = last_keycode;
      register_mods(last_modifier);
      register_code16(pressed_keycode);
      unregister_mods(last_modifier);
    } else {
      unregister_code16(pressed_keycode);
    }
  }
}




bool process_record_user(uint16_t keycode, keyrecord_t *record) {

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

    process_repeat_key(keycode, record);

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
    return update_tri_layer_state(state, _NAV, _NUM, _SYM);
}