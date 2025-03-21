// keymaps/default/keymap.c

#include QMK_KEYBOARD_H

enum layers {
  BASE,
  FN
};

// Custom define for the encoder position
#define ENCODER_CCW  KC_VOLD
#define ENCODER_CW   KC_VOLU
#define ENCODER_PRESS KC_MPLY

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_98_keys(
        // Row 1: 17 keys
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,             KC_PGDN,  KC_PGUP,  KC_DEL,   KC_PSCR,   
        // Row 2: 18 keys
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,   
        // Row 3: 18 keys
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_7,     KC_8,     KC_9,     KC_PPLS,    
        // Row 4: 16 keys
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_P4,    KC_P5,    KC_P6,        
        // Row 5: 17 keys
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_P1,    KC_P2,    KC_P3,    KC_PENT,    
        // Row 6: 12 keys
        KC_LCTL,  MO(1),    KC_LALT,                      KC_SPC,                                 KC_RALT,  MO(1),    KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT   
    ),

    [FN] = LAYOUT_98_keys(
        // Row 1: 17 keys
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  
        // Row 2: 18 keys
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  
        // Row 3: 18 keys
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  
        // Row 4: 16 keys
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,        
        // Row 5: 17 keys
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  
        // Row 6: 12 keys
        _______,  _______,  _______,                      _______,                                _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = { {ENCODER_CCW, ENCODER_CW} },
    [FN]   = { {RGB_VAD, RGB_VAI} }
};
#endif

// Encoder functionality
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        // Different function based on active layer
        if (layer_state_is(FN)) {
            // RGB brightness control when FN layer is active
            if (clockwise) {
                rgb_matrix_increase_val();
            } else {
                rgb_matrix_decrease_val();
            }
        } else {
            // Volume control on base layer
            if (clockwise) {
                tap_code(ENCODER_CW);
            } else {
                tap_code(ENCODER_CCW);
            }
        }
    }
    return true;
}

// Handle encoder button press
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_MEDIA_PLAY_PAUSE && record->event.pressed) {
        tap_code(ENCODER_PRESS);
        return false;
    }
    return true;
}