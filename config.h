#pragma once

/* Enable caps-lock LED*/
#define CAPS_LOCK_LED_INDEX 61

/* Matrix configuration */
#define MATRIX_ROWS 6
#define MATRIX_COLS 18
#define DIODE_DIRECTION ROW2COL
#define MATRIX_ROW_PINS { B5, B4, B3, A15, A14, A13 }
#define MATRIX_COL_PINS { A10, A9, A8, B1, B0, A7, A6, A5, A4, A3, A2, A1, A0, C15, C14, C13, C12, C11 }
#define MATRIX_ROW_SHIFTER ((matrix_row_t)1)

/* RGB Matrix configuration */
#define SNLED27351_I2C_ADDRESS_1 SNLED27351_I2C_ADDRESS_VDDIO
#define SNLED27351_I2C_ADDRESS_2 SNLED27351_I2C_ADDRESS_GND
#define SNLED27351_CURRENT_TUNE { 0xA4, 0xA4, 0x52, 0xA4, 0xA4, 0x52, 0xA4, 0xA4, 0x52, 0xA4, 0xA4, 0x52 }
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_DEFAULT_HUE 0
#define RGB_MATRIX_DEFAULT_SAT 255
#define RGB_MATRIX_DEFAULT_VAL 180

/* I2C configuration */
#define I2C_DRIVER I2C_DRIVER_ST
#define I2C1_SCL_PIN B6
#define I2C1_SDA_PIN B7
#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2

/* Encoder configuration */
#define ENCODER_RESOLUTION 4

/* Bootmagic configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

/* Debounce */
#define DEBOUNCE 5

/* Shift register configuration */
#define NO_PIN_NUM 8
#define NO_PIN_START (MATRIX_COLS - NO_PIN_NUM)
#define NO_PIN_OFFSET 0
#define CLR_REG_VAL 0xFF