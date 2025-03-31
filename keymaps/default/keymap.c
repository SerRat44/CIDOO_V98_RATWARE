/*
 * This file is part of the QMK Firmware for Cidoo V98
 *
 * Copyright (c) 2023 QMK Community
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include QMK_KEYBOARD_H

// Layer definitions
enum cidoo_v98_layers {
    _BASE,
    _FN1,
    _FN2,
    _FN3
};

// Custom keycodes
enum cidoo_v98_keycodes {
    KC_BTPAIR = SAFE_RANGE,  // Bluetooth pairing
    KC_BTSW1,                // Switch to BT profile 1
    KC_BTSW2,                // Switch to BT profile 2
    KC_BTSW3,                // Switch to BT profile 3
    KC_BATSTAT               // Display battery status
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layer: Standard 96% Layout */
    [_BASE] = LAYOUT_cidoo_v98(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE, KC_PSCR, KC_SCRL, KC_PAUS, RGB_TOG,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP, KC_NUM,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, KC_PSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_P7,   KC_P8,   KC_P9,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                    KC_RALT, MO(_FN1),KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P1,   KC_P2,   KC_P3,   KC_PENT
    ),

    /* Function Layer 1 */
    [_FN1] = LAYOUT_cidoo_v98(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BTPAIR, KC_BTSW1, KC_BTSW2, RGB_MOD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_VOLD, KC_MUTE, KC_VOLU,
        _______,          _______, _______, _______, _______, KC_BATSTAT, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_MPRV, KC_MPLY, KC_MNXT, _______,
        _______, _______, _______,                   _______,                   _______, _______, _______, KC_HOME, KC_PGDN, KC_END, KC_MSTP, _______, _______, _______
    ),

    /* Function Layer 2 - VIA Configurable */
    [_FN2] = LAYOUT_cidoo_v98(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Function Layer 3 - VIA Configurable */
    [_FN3] = LAYOUT_cidoo_v98(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

// Encoder mapping
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN1]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [_FN2]  = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [_FN3]  = { ENCODER_CCW_CW(RGB_SAD, RGB_SAI) }
};
#endif

// Handle custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_BTPAIR:
            if (record->event.pressed) {
                // Start BT pairing
                bluetooth_mode_pairing();
            }
            return false;
            
        case KC_BTSW1:
            if (record->event.pressed) {
                // Switch to BT profile 1
                bluetooth_switch_profile(0);
            }
            return false;
            
        case KC_BTSW2:
            if (record->event.pressed) {
                // Switch to BT profile 2
                bluetooth_switch_profile(1);
            }
            return false;
            
        case KC_BTSW3:
            if (record->event.pressed) {
                // Switch to BT profile 3
                bluetooth_switch_profile(2);
            }
            return false;
            
        case KC_BATSTAT:
            if (record->event.pressed) {
                // Display battery status
                uint8_t level = get_battery_level();
                bool charging = is_charging();
                // Visual feedback
                #ifdef RGBLIGHT_ENABLE
                if (charging) {
                    rgblight_sethsv_noeeprom(HSV_GREEN);
                } else if (level > 75) {
                    rgblight_sethsv_noeeprom(HSV_GREEN);
                } else if (level > 50) {
                    rgblight_sethsv_noeeprom(HSV_YELLOW);
                } else if (level > 25) {
                    rgblight_sethsv_noeeprom(HSV_ORANGE);
                } else {
                    rgblight_sethsv_noeeprom(HSV_RED);
                }
                wait_ms(2000);
                rgblight_reload_from_eeprom();
                #endif
            }
            return false;
            
        default:
            return true;
    }
};

// Custom matrix scan code
void matrix_scan_user(void) {
    // Bluetooth tasks
    #ifdef BLUETOOTH_ENABLE
    bluetooth_task();
    #endif
}

// Handle LED indicators
bool led_update_user(led_t led_state) {
    // Turn on/off LEDs based on the state
    if (led_state.caps_lock) {
        // Caps lock indicator
        #ifdef RGBLIGHT_ENABLE
        rgblight_sethsv_at(HSV_RED, 0);
        #endif
    } else {
        // Caps lock off
        #ifdef RGBLIGHT_ENABLE
        rgblight_sethsv_at(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val(), 0);
        #endif
    }
    
    return true;
}

// Encoder actions
bool encoder_update_user(uint8_t index, bool clockwise) {
    // Default actions are defined in encoder_map
    // Add any additional actions here
    return true;
}