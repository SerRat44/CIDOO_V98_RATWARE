#pragma once

// LED driver mapping
#define SNLED27351_DRIVER_COUNT 2
#define SNLED27351_I2C_ADDRESS_1 SNLED27351_I2C_ADDRESS_VDDIO  // 0x74, Driver 1
#define SNLED27351_I2C_ADDRESS_2 SNLED27351_I2C_ADDRESS_GND    // 0x77, Driver 2

// Matrix row shifter for proper shifting behavior
#define MATRIX_ROW_SHIFTER ((matrix_row_t)1)

// VIA optimizations
#define DYNAMIC_KEYMAP_LAYER_COUNT 2