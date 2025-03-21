// cidoo_v98.c

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

// clang-format off

const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/*
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    // First row (17 keys)
    {0, CB9_CA1,    CB7_CA1,    CB8_CA1},
    {0, CB9_CA2,    CB7_CA2,    CB8_CA2},
    {0, CB9_CA3,    CB7_CA3,    CB8_CA3},
    {0, CB9_CA4,    CB7_CA4,    CB8_CA4},
    {0, CB9_CA5,    CB7_CA5,    CB8_CA5},
    {0, CB9_CA6,    CB7_CA6,    CB8_CA6},
    {0, CB9_CA7,    CB7_CA7,    CB8_CA7},
    {0, CB9_CA8,    CB7_CA8,    CB8_CA8},
    {0, CB9_CA9,    CB7_CA9,    CB8_CA9},
    {0, CB9_CA10,   CB7_CA10,   CB8_CA10},
    {0, CB9_CA11,   CB7_CA11,   CB8_CA11},
    {0, CB9_CA12,   CB7_CA12,   CB8_CA12},
    {0, CB9_CA13,   CB7_CA13,   CB8_CA13},
    {0, CB12_CA5,   CB10_CA5,   CB11_CA5},
    {0, CB12_CA6,   CB10_CA6,   CB11_CA6},
    {0, CB9_CA15,   CB7_CA15,   CB8_CA15},
    {0, CB9_CA16,   CB7_CA16,   CB8_CA16},
    
    // Second row (18 keys)
    {0, CB3_CA1,    CB1_CA1,    CB2_CA1},
    {0, CB3_CA2,    CB1_CA2,    CB2_CA2},
    {0, CB3_CA3,    CB1_CA3,    CB2_CA3},
    {0, CB3_CA4,    CB1_CA4,    CB2_CA4},
    {0, CB3_CA5,    CB1_CA5,    CB2_CA5},
    {0, CB3_CA6,    CB1_CA6,    CB2_CA6},
    {0, CB3_CA7,    CB1_CA7,    CB2_CA7},
    {0, CB3_CA8,    CB1_CA8,    CB2_CA8},
    {0, CB3_CA9,    CB1_CA9,    CB2_CA9},
    {0, CB3_CA10,   CB1_CA10,   CB2_CA10},
    {0, CB3_CA11,   CB1_CA11,   CB2_CA11},
    {0, CB3_CA12,   CB1_CA12,   CB2_CA12},
    {0, CB3_CA13,   CB1_CA13,   CB2_CA13},
    {0, CB3_CA14,   CB1_CA14,   CB2_CA14},
    {0, CB3_CA15,   CB1_CA15,   CB2_CA15},
    {0, CB3_CA16,   CB1_CA16,   CB2_CA16},
    {0, CB12_CA7,   CB10_CA7,   CB11_CA7},
    {0, CB12_CA8,   CB10_CA8,   CB11_CA8},
    
    // Third row (18 keys)
    {0, CB6_CA1,    CB4_CA1,    CB5_CA1},
    {0, CB6_CA2,    CB4_CA2,    CB5_CA2},
    {0, CB6_CA3,    CB4_CA3,    CB5_CA3},
    {0, CB6_CA4,    CB4_CA4,    CB5_CA4},
    {0, CB6_CA5,    CB4_CA5,    CB5_CA5},
    {0, CB6_CA6,    CB4_CA6,    CB5_CA6},
    {0, CB6_CA7,    CB4_CA7,    CB5_CA7},
    {0, CB6_CA8,    CB4_CA8,    CB5_CA8},
    {0, CB6_CA9,    CB4_CA9,    CB5_CA9},
    {0, CB6_CA10,   CB4_CA10,   CB5_CA10},
    {0, CB6_CA11,   CB4_CA11,   CB5_CA11},
    {0, CB6_CA12,   CB4_CA12,   CB5_CA12},
    {0, CB6_CA13,   CB4_CA13,   CB5_CA13},
    {0, CB6_CA14,   CB4_CA14,   CB5_CA14},
    {0, CB6_CA15,   CB4_CA15,   CB5_CA15},
    {0, CB6_CA16,   CB4_CA16,   CB5_CA16},
    {0, CB12_CA9,   CB10_CA9,   CB11_CA9},
    {0, CB12_CA10,  CB10_CA10,  CB11_CA10},
    
    // Fourth row (16 keys)
    {1, CB3_CA16,   CB1_CA16,   CB2_CA16},
    {1, CB3_CA15,   CB1_CA15,   CB2_CA15},
    {1, CB3_CA14,   CB1_CA14,   CB2_CA14},
    {1, CB3_CA13,   CB1_CA13,   CB2_CA13},
    {1, CB3_CA12,   CB1_CA12,   CB2_CA12},
    {1, CB3_CA11,   CB1_CA11,   CB2_CA11},
    {1, CB3_CA10,   CB1_CA10,   CB2_CA10},
    {1, CB3_CA9,    CB1_CA9,    CB2_CA9},
    {1, CB3_CA8,    CB1_CA8,    CB2_CA8},
    {1, CB3_CA7,    CB1_CA7,    CB2_CA7},
    {1, CB3_CA6,    CB1_CA6,    CB2_CA6},
    {1, CB3_CA5,    CB1_CA5,    CB2_CA5},
    {1, CB12_CA3,   CB10_CA3,   CB11_CA3},
    {1, CB12_CA4,   CB10_CA4,   CB11_CA4},
    {1, CB12_CA5,   CB10_CA5,   CB11_CA5},
    {1, CB3_CA3,    CB1_CA3,    CB2_CA3},
    
    // Fifth row (17 keys)
    {1, CB9_CA16,   CB7_CA16,   CB8_CA16},
    {1, CB9_CA14,   CB7_CA14,   CB8_CA14},
    {1, CB9_CA13,   CB7_CA13,   CB8_CA13},
    {1, CB9_CA12,   CB7_CA12,   CB8_CA12},
    {1, CB9_CA11,   CB7_CA11,   CB8_CA11},
    {1, CB9_CA10,   CB7_CA10,   CB8_CA10},
    {1, CB9_CA9,    CB7_CA9,    CB8_CA9},
    {1, CB9_CA8,    CB7_CA8,    CB8_CA8},
    {1, CB9_CA7,    CB7_CA7,    CB8_CA7},
    {1, CB9_CA6,    CB7_CA6,    CB8_CA6},
    {1, CB9_CA5,    CB7_CA5,    CB8_CA5},
    {1, CB9_CA4,    CB7_CA4,    CB8_CA4},
    {1, CB9_CA3,    CB7_CA3,    CB8_CA3},
    {1, CB9_CA2,    CB7_CA2,    CB8_CA2},
    {1, CB9_CA1,    CB7_CA1,    CB8_CA1},
    {1, CB12_CA11,  CB10_CA11,  CB11_CA11},
    {1, CB12_CA12,  CB10_CA12,  CB11_CA12},
    
    // Sixth row (12 keys)
    {1, CB6_CA16,   CB4_CA16,   CB5_CA16},
    {1, CB6_CA15,   CB4_CA15,   CB5_CA15},
    {1, CB6_CA14,   CB4_CA14,   CB5_CA14},
    {1, CB6_CA9,    CB4_CA9,    CB5_CA9},
    {1, CB6_CA4,    CB4_CA4,    CB5_CA4},
    {1, CB6_CA3,    CB4_CA3,    CB5_CA3},
    {1, CB6_CA2,    CB4_CA2,    CB5_CA2},
    {1, CB6_CA1,    CB4_CA1,    CB5_CA1},
    {1, CB12_CA14,  CB10_CA14,  CB11_CA14},
    {1, CB12_CA15,  CB10_CA15,  CB11_CA15},
    {1, CB12_CA16,  CB10_CA16,  CB11_CA16},
    {1, CB12_CA2,   CB10_CA2,   CB11_CA2},
    
    // The following are the underglow/backlight strip LEDs, numbered 98-105
    {1, CB12_CA6,    CB10_CA6,    CB11_CA6},
    {1, CB12_CA7,    CB10_CA7,    CB11_CA7},
    {1, CB12_CA8,    CB10_CA8,    CB11_CA8},
    {1, CB12_CA9,    CB10_CA9,    CB11_CA9},
    {1, CB12_CA10,   CB10_CA10,   CB11_CA10},
    {1, CB12_CA11,   CB10_CA11,   CB11_CA11},
    {1, CB12_CA12,   CB10_CA12,   CB11_CA12},
    {1, CB12_CA2,    CB10_CA2,    CB11_CA2},
};

#define __ NO_LED
#define BACKLIGHT_START_INDEX 98
#define BACKLIGHT_LED_COUNT 8

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index based on the new layout with no LED for encoder
        { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, __, 13, 14, 15, 16 },
        { 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34 },
        { 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52 },
        { 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, __, 65, 66, 67, 68, __ },
        { 69, __, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85 },
        { 86, 87, 88, __, __, __, 89, __, __, __, 89, 90, 91, 92, 93, 94, 95, __ },
    },
    {
        // LED Index to Physical Position
        // First row (17 keys)
        {0,0}, {20,0}, {30,0}, {40,0}, {50,0}, {65,0}, {75,0}, {85,0}, {95,0}, {110,0}, {120,0}, {130,0}, {140,0}, {160,0}, {175,0}, {185,0}, {205,0},
        // Second row (18 keys)
        {0,15}, {15,15}, {25,15}, {35,15}, {45,15}, {55,15}, {65,15}, {75,15}, {85,15}, {95,15}, {105,15}, {115,15}, {125,15}, {140,15}, {160,15}, {175,15}, {185,15}, {195,15},
        // Third row (18 keys)
        {3,25}, {18,25}, {28,25}, {38,25}, {48,25}, {58,25}, {68,25}, {78,25}, {88,25}, {98,25}, {108,25}, {118,25}, {128,25}, {143,25}, {160,25}, {175,25}, {185,25}, {195,25},
        // Fourth row (16 keys)
        {5,35}, {20,35}, {30,35}, {40,35}, {50,35}, {60,35}, {70,35}, {80,35}, {90,35}, {100,35}, {110,35}, {125,35}, {143,35}, {160,35}, {175,35}, {185,35},
        // Fifth row (17 keys)
        {8,45}, {25,45}, {35,45}, {45,45}, {55,45}, {65,45}, {75,45}, {85,45}, {95,45}, {105,45}, {115,45}, {130,45}, {143,45}, {160,45}, {175,45}, {185,45}, {195,45},
        // Sixth row (12 keys)
        {5,55}, {18,55}, {30,55}, {75,55}, {110,55}, {123,55}, {136,55}, {149,55}, {143,45}, {175,55}, {185,55}, {195,55},
        
        // Backlight LED positions (front LED strip)
        {20,64}, {50,64}, {80,64}, {110,64}, {140,64}, {170,64}, {200,64}, {230,64}
    },
    {
        // RGB LED Index to Flag
        // First row (17 keys)
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        // Second row (18 keys)
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1,
        // Third row (18 keys)
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1,
        // Fourth row (16 keys)
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1,
        // Fifth row (17 keys)
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1,
        // Sixth row (12 keys)
        1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1,
        
        // Backlight flags (32 = underglow/strip)
        32, 32, 32, 32, 32, 32, 32, 32
    }
};

#endif // RGB_MATRIX_ENABLE

#ifdef BACKLIGHT_ENABLE

void backlight_init_ports(void) {
    // Setup backlight pin as output
    setPinOutput(B7);
    // Turn backlight on
    writePinHigh(B7);
}

void backlight_set(uint8_t level) {
    // For regular backlight control
    if (level > 0) {
        writePinHigh(B7);
    } else {
        writePinLow(B7);
    }
}

#endif // BACKLIGHT_ENABLE

#ifdef DIP_SWITCH_ENABLE

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    if (index == 0) {
        default_layer_set(1UL << (active ? 2 : 0));
    }
    return true;
}

#endif // DIP_SWITCH_ENABLE

// RGB Matrix toggle handling
#ifdef RGB_MATRIX_ENABLE

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case QK_RGB_MATRIX_TOGGLE:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                    } break;
                }
            }
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_set_flags(LED_FLAG_ALL);
                rgb_matrix_enable();
            }
            return false;
    }
    return true;
}

#endif // RGB_MATRIX_ENABLE