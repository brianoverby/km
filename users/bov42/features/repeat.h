#pragma once
#include QMK_KEYBOARD_H

// Repeat key implementation - credit to KapJI and precondition
// When you send 'repeat_keycode' the previous keycode + modifiers are repeated

// To use it, just include 'repeat.h' in your keymap file and add 'SRC += features/repeat.c' to your rules.mk
// Define a repeat keycode (fx REPEAT). Then call the function in 'process_record_user'
// process_repeat_key(keycode, record, REPEAT);

void process_repeat_key(
    uint16_t keycode,
    const keyrecord_t *record,
    uint16_t repeat_keycode
    );