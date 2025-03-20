#include "matrix.h"
#include "atomic_util.h"
#include <string.h>

// Pin connected to DS of 74HC595
#define DATA_PIN C15
// Pin connected to SH_CP of 74HC595
#define CLOCK_PIN A1
// Pin connected to ST_CP of 74HC595
#define LATCH_PIN A0

#ifdef MATRIX_ROW_PINS
static pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
#endif // MATRIX_ROW_PINS
#ifdef MATRIX_COL_PINS
static pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#endif // MATRIX_COL_PINS

#define ROWS_PER_HAND (MATRIX_ROWS)

#ifndef NO_PIN
#    define NO_PIN PIN_NONE
#endif

static inline void gpio_atomic_set_pin_output_low(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_low(pin);
    }
}

static inline void gpio_atomic_set_pin_output_high(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_high(pin);
    }
}

static inline void gpio_atomic_set_pin_input_high(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_input_high(pin);
    }
}

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return gpio_read_pin(pin);
    } else {
        return 1;
    }
}

static void shiftOut(uint16_t dataOut) {
    for (uint8_t i = 0; i < NO_PIN_NUM; i++) {
        if (dataOut & 0x1) {
            gpio_atomic_set_pin_output_high(DATA_PIN);
        } else {
            gpio_atomic_set_pin_output_low(DATA_PIN);
        }
        dataOut = dataOut >> 1;
        gpio_atomic_set_pin_output_high(CLOCK_PIN);
        gpio_atomic_set_pin_output_low(CLOCK_PIN);
    }
    gpio_atomic_set_pin_output_high(LATCH_PIN);
    gpio_atomic_set_pin_output_low(LATCH_PIN);
}

static void shiftout_single(uint8_t data) {
    if (data & 0x1) {
        gpio_atomic_set_pin_output_high(DATA_PIN);
    } else {
        gpio_atomic_set_pin_output_low(DATA_PIN);
    }
    gpio_atomic_set_pin_output_high(CLOCK_PIN);
    gpio_atomic_set_pin_output_low(CLOCK_PIN);

    gpio_atomic_set_pin_output_high(LATCH_PIN);
    gpio_atomic_set_pin_output_low(LATCH_PIN);
}

static bool select_col(uint8_t col) {
    pin_t pin = col_pins[col];

    if (pin != NO_PIN) {
        gpio_atomic_set_pin_output_low(pin);
        return true;
    } else {
        if (col == NO_PIN_START) {
            shiftout_single(0x00);
        } else {
            shiftout_single(0x01);
        }
        return true;
    }
    return false;
}

static void unselect_col(uint8_t col) {
    pin_t pin = col_pins[col];

    if (pin != NO_PIN) {
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
        gpio_atomic_set_pin_output_high(pin);
#else
        gpio_atomic_set_pin_input_high(pin);
#endif
    } else {
        if (col == (MATRIX_COLS - NO_PIN_OFFSET - 1)) {
            gpio_atomic_set_pin_output_high(CLOCK_PIN);
            gpio_atomic_set_pin_output_low(CLOCK_PIN);
            gpio_atomic_set_pin_output_high(LATCH_PIN);
            gpio_atomic_set_pin_output_low(LATCH_PIN);
        }
    }
}

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        pin_t pin = col_pins[x];
        if (pin != NO_PIN) {
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
            gpio_atomic_set_pin_output_high(pin);
#else
            gpio_atomic_set_pin_input_high(pin);
#endif
        }
        if (x == (MATRIX_COLS - NO_PIN_OFFSET - 1))
            // unselect shift Register
            shiftOut(CLR_REG_VAL);
    }
}

static void matrix_init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (row_pins[x] != NO_PIN) {
            gpio_atomic_set_pin_input_high(row_pins[x]);
        }
    }
}

static void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {
    bool key_pressed = false;

    // Select col
    if (!select_col(current_col)) { // select col
        return;                     // skip NO_PIN col
    }

    if (current_col < 10) {
        matrix_output_select_delay();
    } else {
        for (int8_t cycle = 4; cycle > 0; cycle--) {
            matrix_output_select_delay(); // 0.25us
            matrix_output_select_delay();
            matrix_output_select_delay();
            matrix_output_select_delay();
        }
    }

    // For each row...
    for (uint8_t row_index = 0; row_index < ROWS_PER_HAND; row_index++) {
        // Check row pin state
        if (readMatrixPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= row_shifter;
            key_pressed = true;
        } else {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~row_shifter;
        }
    }

    // Unselect col
    unselect_col(current_col);
    matrix_output_unselect_delay(current_col, key_pressed); // wait for all Row signals to go HIGH
}

void matrix_init_custom(void) {
    // initialize key pins
    matrix_init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    // Set col, read rows
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++, row_shifter <<= 1) {
        matrix_read_rows_on_col(curr_matrix, current_col, row_shifter);
    }

    bool changed = memcmp(current_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) memcpy(current_matrix, curr_matrix, sizeof(curr_matrix));

    return changed;
}