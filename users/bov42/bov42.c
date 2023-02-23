#include QMK_KEYBOARD_H
#include "features/swapper.h"
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

    NEW_SAFE_RANGE
};

// Combos defined in combos.def
#if defined(COMBO_ENABLE)
#include "g/keymap_combo.h"
#endif


// One Shot Modifiers 
#define OSM_SFT OSM(MOD_LSFT)

// Layer change
#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_bov42(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    DK_SCLN, DK_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    COMMA,   DOT,     DK_SLSH, KC_TAB,
                                            KC_LCMD, LA_NAV,  KC_SPC,           KC_ENT,  LA_SYM,  KC_LALT   
    ),

    [_NAV] = LAYOUT_bov42(
        KC_TAB,  LOCK,    SW_WIN,  SEARCH,  KC_VOLD, KC_VOLU,                            KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                             KC_F11,  KC_F12,  DK_AE,   DK_OE,   DK_AA,   _______,
                                            _______, _______, _______,          _______, KC_DEL,  _______
    ),

    [_SYM] = LAYOUT_bov42(
        _______, DK_EXLM, AT,      DK_HASH, DLR,     DK_PERC,                            DK_CIRC, DK_AMPR, DK_ASTR, DK_LPRN, DK_RPRN, BSLS,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               DK_MINS, DK_EQL,  DK_GRV,  LCBR,    RCBR,    PIPE,
        _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                               DK_UNDS, DK_PLUS, DK_TILD, DK_LBRC, DK_RBRC, _______,
                                            _______, _______, _______,          _______, _______, _______
    )
};


// This is a hack to match US keycap legends on a Danish keyboard layout - using Key Override
//const key_override_t shift_comm_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_GRV);
//const key_override_t shift_dot_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, S(KC_GRV));
const key_override_t shift_quot_key_override = ko_make_basic(MOD_MASK_SHIFT, DK_QUOT, DK_DQUO);
const key_override_t shift_scln_key_override = ko_make_basic(MOD_MASK_SHIFT, DK_SCLN, DK_COLN); 
const key_override_t shift_slsh_key_override = ko_make_basic(MOD_MASK_SHIFT, DK_SLSH, DK_QUES); 

// Key Override array
const key_override_t **key_overrides = (const key_override_t *[]){
    //&shift_comm_key_override,
    //&shift_dot_key_override,
    &shift_quot_key_override,
    &shift_scln_key_override,
    &shift_slsh_key_override,
    NULL
};


bool sw_win_active = false;


// Send Mac or PC keycode
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


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // Check for Windows or macOS before updating swapper
    uint16_t WINSW_KEY = (keymap_config.swap_lctl_lgui) ? KC_LALT : KC_LCMD;

    update_swapper(
            &sw_win_active, WINSW_KEY, KC_TAB, SW_WIN,
            keycode, record
        );

    // Layer lock, remember to define the LLOCK keycode
    if (!process_layer_lock(keycode, record, LLOCK)) { return false; }

    const uint8_t mods = get_mods() | get_oneshot_mods() | get_weak_mods();

    switch (keycode) {

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
