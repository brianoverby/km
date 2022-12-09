#include QMK_KEYBOARD_H
#include "features/oneshot.h"
#include "features/swapper.h"
#include "features/repeat.h"
#include "features/layer_lock.h"
#include "defines_dk.h"


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
    LLOCK,
    SEARCH,
    SW_WIN,
    REPEAT,

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

// Layer change
#define LA_NAV MO(_NAV)
#define LA_NUM MO(_NUM)

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
                                   LA_NAV,  OSM_SFT,                   KC_SPC,  LA_NUM   
    ),

    [_NAV] = LAYOUT_bov34(
        KC_ESC,  KC_VOLD, KC_VOLU, SW_WIN,  REPEAT,                    KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  SEARCH,                    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT,
        UNDO,    CUT,     COPY,    PSTE,    LOCK,                      KC_TAB,  DK_AE,   DK_OE,   DK_AA,   XXXXXXX,
                                   _______, LLOCK,                     KC_BSPC, _______
    ),
    
    [_NUM] = LAYOUT_bov34(
        KC_F11,  KC_7,    KC_8,    KC_9,    DK_MINS,                   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
        KC_F12,  KC_4,    KC_5,    KC_6,    KC_COMM,                   XXXXXXX, OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
        KC_TAB,  KC_1,    KC_2,    KC_3,    KC_DOT,                    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                                   _______, KC_0,                      LLOCK,   _______
    ),

    [_SYM] = LAYOUT_bov34(
        DK_EXLM, AT,      DK_HASH, DLR,     DK_PERC,                   XXXXXXX, DK_LPRN, DK_RPRN, DK_CIRC, DK_TILD,
        DK_AMPR, DK_ASTR, DK_UNDS, DK_QUOT, DK_DQUO,                   XXXXXXX, LCBR,    RCBR,    DK_ACUT, DK_GRV,
        PIPE,    DK_PLUS, DK_MINS, DK_EQL,  BSLS,                      XXXXXXX, DK_LBRC, DK_RBRC, DK_DIAE, XXXXXXX,
                                   _______, XXXXXXX,                   XXXXXXX, _______
    )
};


// Key overrides
const key_override_t comma_labk = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, DK_LABK);
const key_override_t dot_rabk = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, DK_RABK);
const key_override_t quote_dblquote = ko_make_basic(MOD_MASK_SHIFT, DK_QUOT, DK_DQUO);
const key_override_t semicolon_colon = ko_make_basic(MOD_MASK_SHIFT, DK_SCLN, DK_COLN); 
const key_override_t slash_question = ko_make_basic(MOD_MASK_SHIFT, DK_SLSH, DK_QUES);
const key_override_t backspace_delete = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t space_underscore = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, DK_UNDS);

// Key override array
const key_override_t **key_overrides = (const key_override_t *[]){
    &comma_labk,
    &dot_rabk,
    &quote_dblquote, 
    &semicolon_colon,
    &slash_question,
    &backspace_delete,
    &space_underscore,
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


// Send Mac or PC keycode
void send_mac_or_pc(uint16_t mac_keycode, uint16_t pc_keycode, bool is_pressed) {
    uint16_t code = (user_config.macos) ? mac_keycode : pc_keycode;
    if(is_pressed) {
        register_code16(code);
    } else {
        unregister_code16(code);
    }
}

// Added DK keycodes to CAPS_WORD
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_MINS:
        case KC_UNDS:
        case DK_MINS:
        case DK_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}


layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NAV, _NUM, _SYM);
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

    // Repeat key, remember to define the REPEAT keycode
    process_repeat_key(keycode, record, REPEAT);

    // Layer lock, remember to define the LLOCK keycode
    if (!process_layer_lock(keycode, record, LLOCK)) { return false; }

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
            send_mac_or_pc(MAC_AT, PC_AT, (record->event.pressed));
            return false;
        break;
        case DLR:
            send_mac_or_pc(MAC_DLR, PC_DLR, (record->event.pressed));
            return false;
        break;
        case BSLS:
            send_mac_or_pc(MAC_BSLS, PC_BSLS, (record->event.pressed));
            return false;
        break;
        case PIPE:
            send_mac_or_pc(MAC_PIPE, PC_PIPE, (record->event.pressed));
            return false;
        break;
        case LCBR:
            send_mac_or_pc(MAC_LCBR, PC_LCBR, (record->event.pressed));
            return false;
        break;
        case RCBR:
            send_mac_or_pc(MAC_RCBR, PC_RCBR, (record->event.pressed));
            return false;
        break;
        case PND:
            send_mac_or_pc(MAC_PND, PC_PND, (record->event.pressed));
            return false;
        break;
        case EURO:
            send_mac_or_pc(MAC_EURO, PC_EURO, (record->event.pressed));
            return false;
        break;
        case UNDO:
            send_mac_or_pc(MAC_UNDO, PC_UNDO, (record->event.pressed));
            return false;
        break;
        case CUT:
            send_mac_or_pc(MAC_CUT, PC_CUT, (record->event.pressed));
            return false;
        break;
        case COPY:
            send_mac_or_pc(MAC_COPY, PC_COPY, (record->event.pressed));
            return false;
        break;
        case PSTE:
            send_mac_or_pc(MAC_PSTE, PC_PSTE, (record->event.pressed));
            return false;
        break;
        case LOCK:
            send_mac_or_pc(MAC_LOCK, PC_LOCK, (record->event.pressed));
            return false;
        break;
        case SEARCH:
            send_mac_or_pc(MAC_SEARCH, PC_SEARCH, (record->event.pressed));
            return false;
        break;

    }

    return true;
}
