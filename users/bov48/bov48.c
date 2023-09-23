#include QMK_KEYBOARD_H
#include "defines_dk.h"


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

// Layer change
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define FN MO(_FN)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_bov48(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    DK_SCLN, DK_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    COMMA,   DOT,     DK_SLSH, KC_ENT,
        FN,      KC_LCTL, KC_LALT, KC_LCMD, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT   
    ),
    [_RAISE] = LAYOUT_bov48(
        DK_TILD, DK_EXLM, AT,      DK_HASH, DLR,     DK_PERC, DK_CIRC, DK_AMPR, DK_ASTR, DK_LPRN, DK_RPRN, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DK_UNDS, DK_PLUS, LCBR,    RCBR,    DK_ACUT,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DK_MINS, DK_EQL,  DK_LBRC, DK_RBRC, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, BSLS,    PIPE,    XXXXXXX, XXXXXXX   
    ),
    [_LOWER] = LAYOUT_bov48(
        DK_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  DK_DIAE,
        _______, KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, COMMA,   DOT,     DK_SLSH, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT   
    ),
    [_FN] = LAYOUT_bov48(
        KC_TAB,  KC_7,    KC_8,    KC_9,    XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU, KC_INS,  XXXXXXX, KC_PSCR, KC_DEL,
        XXXXXXX, KC_4,    KC_5,    KC_6,    XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX, DK_AE,   DK_OE,   DK_AA,   
        _______, KC_1,    KC_2,    KC_3,    KC_0,    XXXXXXX, XXXXXXX, KC_MUTE, COMMA,   DOT,     DK_SLSH, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END   
    )
};



// Key overrides
//const key_override_t comma_labk = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, DK_LABK);
//const key_override_t dot_rabk = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, DK_RABK);
const key_override_t quote_dblquote = ko_make_basic(MOD_MASK_SHIFT, DK_QUOT, DK_DQUO);
const key_override_t semicolon_colon = ko_make_basic(MOD_MASK_SHIFT, DK_SCLN, DK_COLN); 
const key_override_t slash_question = ko_make_basic(MOD_MASK_SHIFT, DK_SLSH, DK_QUES);

// Key override array
const key_override_t **key_overrides = (const key_override_t *[]){
    //&comma_labk,
    //&dot_rabk,
    &quote_dblquote, 
    &semicolon_colon,
    &slash_question,
    NULL
};


void send_mac_or_pc(uint16_t mac_keycode, uint16_t pc_keycode, bool is_pressed) {
    uint16_t code = (keymap_config.swap_lctl_lgui) ?  pc_keycode : mac_keycode;
    if(is_pressed) {
        register_code16(code);
    } else {
        unregister_code16(code);
    }
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {

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
