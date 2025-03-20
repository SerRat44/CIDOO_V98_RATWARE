#include QMK_KEYBOARD_H

// clang-format off

enum layers{
  MAC_BASE,
  MAC_FN,
  WIN_BASE,
  WIN_FN,
  MAC_FN2,  // New layer for Mac when both Fn keys are pressed
  WIN_FN2   // New layer for Windows when both Fn keys are pressed
};

// Custom define for the encoder position
#define ENCODER_CCW  KC_VOLD
#define ENCODER_CW   KC_VOLU
#define ENCODER_PRESS KC_MUTE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_NO,    KC_NO,    RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,              KC_F14,   KC_F15,   KC_F16,   KC_F17,   
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,    KC_INS,   KC_HOME,  KC_PGUP,  KC_NUM,   
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,    KC_DEL,   KC_END,   KC_PGDN,  KC_P7,    
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,     KC_P8,    KC_P9,    KC_PMNS,        
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,    KC_P4,    KC_P5,    KC_P6,    KC_PPLS,    
        KC_LCTL,  KC_LOPT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD,  KC_ROPT,  MO(MAC_FN),LT(MAC_FN2, KC_RCTL), KC_P1,    KC_P2,    KC_P3),

    [MAC_FN] = LAYOUT(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,              _______,  _______,  _______,  _______,  
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,    _______,  _______,  _______,        
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,            _______,    _______,  _______,  _______,  _______,  
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  MO(MAC_FN2), _______,  _______,  _______),
        
    [MAC_FN2] = LAYOUT(
        RESET,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  
        _______,  RGB_M_P,  RGB_M_B,  RGB_M_R,  RGB_M_SW, RGB_M_SN, RGB_M_K,  RGB_M_X,  RGB_M_G,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  
        _______,  RGB_M_T,  RGB_M_TW, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,    _______,  _______,  _______,        
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,    _______,  _______,  _______,  _______,  
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,    _______,  _______,  _______),

    [WIN_BASE] = LAYOUT(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,              _______,  _______,  _______,  _______,  
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,    KC_INS,   KC_HOME,  KC_PGUP,  KC_NUM,   
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,    KC_DEL,   KC_END,   KC_PGDN,  KC_P7,    
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,     KC_P8,    KC_P9,    KC_PMNS,        
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,    KC_P4,    KC_P5,    KC_P6,    KC_PPLS,   
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RWIN,  MO(WIN_FN),LT(WIN_FN2, KC_RCTL), KC_P1,    KC_P2,    KC_P3),

    [WIN_FN] = LAYOUT(
        _______,  KC_BRID,  KC_BRIU,  _______,  _______,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,              _______,  _______,  _______,  _______,  
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,    _______,  _______,  _______,        
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,            _______,    _______,  _______,  _______,  _______,   
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  MO(WIN_FN2), _______,  _______,  _______),
        
    [WIN_FN2] = LAYOUT(
        RESET,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  
        _______,  RGB_M_P,  RGB_M_B,  RGB_M_R,  RGB_M_SW, RGB_M_SN, RGB_M_K,  RGB_M_X,  RGB_M_G,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  
        _______,  RGB_M_T,  RGB_M_TW, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,    _______,  _______,  _______,        
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,    _______,  _______,  _______,  _______,   
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,    _______,  _______,  _______),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = { ENCODER_CCW, ENCODER_CW },
    [MAC_FN1]   = { ENCODER_CCW, ENCODER_CW },
    [MAC_FN2]  = { ENCODER_CCW, ENCODER_CW },
    [WIN_BASE] = { ENCODER_CCW, ENCODER_CW },
    [WIN_FN1]   = { ENCODER_CCW, ENCODER_CW },
    [WIN_FN2]  = { ENCODER_CCW, ENCODER_CW }
};
#endif

// Add encoder functionality
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(ENCODER_CW);
        } else {
            tap_code(ENCODER_CCW);
        }
    }
    return true;
}

// Handle encoder press if your encoder is also a button
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If encoder button is pressed (your hardware should map this to a specific keycode)
    if (keycode == KC_MEDIA_PLAY_PAUSE && record->event.pressed) {
        tap_code(ENCODER_PRESS);
        return false;
    }
    return true;
}