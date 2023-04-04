#include QMK_KEYBOARD_H
#include "features/oneshot.h"
#include "features/swapper.h"
#include "features/repeat.h"
#include "features/layer_lock.h"
#include "defines_dk.h"


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
    AT = SAFE_RANGE,
    DLR,
    BSLS,
    PIPE,
    LCBR,
    RCBR,
    LABK,
    RABK,
    PND,
    EURO,

    DOT,
    COMMA,

    UNDO,
    CUT,
    COPY,
    PSTE,

    LOCK,
    LLOCK,
    SEARCH,
    SW_WIN,
    REPEAT,

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
#define LA_SYM MO(_SYM)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_bov34(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    DK_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    COMMA,   DOT,     DK_SLSH,
                                   LA_NAV,  OSM_SFT,                   KC_SPC,  LA_SYM   
    ),

    [_SYM] = LAYOUT_bov34(
        DK_EXLM, AT,      DK_HASH, DLR,     DK_PERC,                   DK_CIRC, DK_TILD, DK_LPRN, DK_RPRN, KC_BSPC,
        DK_AMPR, DK_ASTR, DK_UNDS, DK_QUOT, DK_DQUO,                   DK_GRV,  DK_ACUT, LCBR,    RCBR,    KC_DEL,
        PIPE,    DK_PLUS, DK_MINS, DK_EQL,  BSLS,                      XXXXXXX, DK_DIAE, DK_LBRC, DK_RBRC, KC_ENT,
                                   _______, _______,                   _______, _______
    ),

    [_NAV] = LAYOUT_bov34(
        KC_ESC,  SW_WIN,  SEARCH,  REPEAT,  KC_TAB,                    KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_BSPC,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  XXXXXXX,                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,
        UNDO,    CUT,     COPY,    PSTE,    LOCK,                      CG_TOGG, DK_AE,   DK_OE,   DK_AA,   KC_ENT,
                                   _______, _______,                   _______, _______
    ),
    
    [_NUM] = LAYOUT_bov34(
        XXXXXXX, KC_7,    KC_8,    KC_9,    KC_TAB,                    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_BSPC,
        KC_COMM, KC_4,    KC_5,    KC_6,    XXXXXXX,                   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_DEL,
        KC_DOT,  KC_1,    KC_2,    KC_3,    KC_0,                      KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_ENT,
                                   _______, _______,                   _______, _______
    )

};


// Key overrides
//const key_override_t comma_labk = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, DK_LABK);
//const key_override_t dot_rabk = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, DK_RABK);
const key_override_t quote_dblquote = ko_make_basic(MOD_MASK_SHIFT, DK_QUOT, DK_DQUO);
const key_override_t semicolon_colon = ko_make_basic(MOD_MASK_SHIFT, DK_SCLN, DK_COLN); 
const key_override_t slash_question = ko_make_basic(MOD_MASK_SHIFT, DK_SLSH, DK_QUES);
const key_override_t backspace_delete = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t space_underscore = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, DK_UNDS);

// Key override array
const key_override_t **key_overrides = (const key_override_t *[]){
    //&comma_labk,
    //&dot_rabk,
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
        case LA_SYM:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LA_NAV:
        case LA_SYM:
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


void send_mac_or_pc(uint16_t mac_keycode, uint16_t pc_keycode, bool is_pressed) {
    uint16_t code = (keymap_config.swap_lctl_lgui) ?  pc_keycode : mac_keycode;
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
    return update_tri_layer_state(state, _NAV, _SYM, _NUM);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // Check for Windows or macOS before updating swapper
    uint16_t WINSW_KEY = (keymap_config.swap_lctl_lgui) ? KC_LALT : KC_LCMD;

    // Support Magic swap in callum oneshot
    uint16_t CMD_KEY = (keymap_config.swap_lctl_lgui) ? KC_LCTL : KC_LCMD;
    uint16_t CTRL_KEY = (keymap_config.swap_lctl_lgui) ? KC_LCMD : KC_LCTL;

    update_swapper(
            &sw_win_active, WINSW_KEY, KC_TAB, SW_WIN,
            keycode, record
        );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, CTRL_KEY, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, CMD_KEY, OS_CMD,
        keycode, record
    );

    // Repeat key, remember to define the REPEAT keycode
    process_repeat_key(keycode, record, REPEAT);

    // Layer lock, remember to define the LLOCK keycode
    if (!process_layer_lock(keycode, record, LLOCK)) { return false; }

    const uint8_t mods = get_mods() | get_oneshot_mods() | get_weak_mods();

    switch (keycode) {

        // key_override does not work as intended for comma and dot 
        case COMMA:
            if (record->event.pressed) {
                if (mods & MOD_MASK_SHIFT) {
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    unregister_mods(MOD_MASK_SHIFT);
                    uint16_t code = (keymap_config.swap_lctl_lgui) ?  PC_LABK : MAC_LABK;
                    tap_code(code);
                    register_mods(mods);
                }
                else {
                    tap_code(KC_COMM);
                }
            }
            return false;
        case DOT:
            if (record->event.pressed) {
                if (mods & MOD_MASK_SHIFT) {
                    uint16_t code = (keymap_config.swap_lctl_lgui) ?  PC_RABK : MAC_RABK;
                    tap_code(code);
                    register_mods(mods);
                }
                else {
                    tap_code(KC_DOT);
                }
            }
            return false;

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
        case LABK:
            send_mac_or_pc(MAC_LABK, PC_LABK, (record->event.pressed));
            return false;
        break;
        case RABK:
            send_mac_or_pc(MAC_RABK, PC_RABK, (record->event.pressed));
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
