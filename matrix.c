/*
 * This file is part of the QMK Firmware for Cidoo V98
 *
 * Copyright (c) 2023 QMK Community
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "quantum.h"
#include "matrix.h"
#include "debounce.h"
#include "wait.h"
#include "debug.h"
#include "gpio.h"
#include "cidoo_v98.h"

/* 96% keyboard typically uses a 12x9 matrix (12 columns, 9 rows) */
#define ROWS_PER_HAND 9
#define COLS_PER_HAND 12

/* Pin configuration for rows and columns */
static const pin_t row_pins[ROWS_PER_HAND] = MATRIX_ROW_PINS;
static const pin_t col_pins[COLS_PER_HAND] = MATRIX_COL_PINS;

/* Matrix state arrays */
static matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
static matrix_row_t matrix[MATRIX_ROWS];      // debounced values
static matrix_row_t prev_matrix[MATRIX_ROWS] = {0};  // previous state for detection

/* Matrix state tracking for bluetooth/wired mode */
static bool matrix_has_changed = false;
static uint8_t current_mode = MATRIX_MODE_WIRED;  // Start in wired mode by default

#ifdef MATRIX_POWER_SAVE
static uint32_t matrix_timer = 0;
static bool matrix_power_saving = false;
#endif

/**
 * Initialize matrix hardware.
 */
void matrix_init_custom(void) {
    debug_enable = true;
    debug_matrix = true;
    
    // Initialize all pins
    for (uint8_t i = 0; i < ROWS_PER_HAND; i++) {
        setPinInputHigh(row_pins[i]);
    }
    
    for (uint8_t i = 0; i < COLS_PER_HAND; i++) {
        setPinOutput(col_pins[i]);
        writePinHigh(col_pins[i]);
    }
    
    // Initialize matrix state
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i] = 0;
    }
    
    // Initialize bluetooth module if available
#ifdef BLUETOOTH_ENABLE
    bluetooth_init();
#endif

    // Initialize debouncing
    debounce_init(MATRIX_ROWS);
    
    // Ensure everything is properly set
    matrix_init_quantum();
}

/**
 * Scan the physical matrix and update internal matrix state.
 * 
 * This allows support for both wired and wireless connections.
 */
bool matrix_scan_custom(void) {
    bool changed = false;
    
    // Check connection mode (USB or Bluetooth)
#ifdef BLUETOOTH_ENABLE
    if (USB_DeviceState != DEVICE_STATE_Configured) {
        // If USB not connected, switch to Bluetooth mode
        if (current_mode == MATRIX_MODE_WIRED) {
            bluetooth_mode_enable();
            current_mode = MATRIX_MODE_BT;
        }
    } else {
        // If USB connected, switch to wired mode
        if (current_mode == MATRIX_MODE_BT) {
            bluetooth_mode_disable();
            current_mode = MATRIX_MODE_WIRED;
        }
    }
#endif

#ifdef MATRIX_POWER_SAVE
    // Implement power-saving feature to conserve battery
    // If no key has been pressed for a while, scan less frequently
    if (timer_elapsed32(matrix_timer) > MATRIX_POWER_SAVE_TIMEOUT) {
        if (!matrix_power_saving) {
            matrix_power_saving = true;
        }
        
        // When in power-saving mode, only scan matrix occasionally
        if (timer_elapsed32(matrix_timer) < MATRIX_POWER_SAVE_TIMEOUT + 500) {
            return matrix_has_changed;
        }
        
        matrix_timer = timer_read32();
    } else if (matrix_power_saving) {
        matrix_power_saving = false;
    }
#endif

    // Save previous state for comparison
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        prev_matrix[i] = matrix[i];
    }
    
    // Scan the physical matrix
    for (uint8_t current_col = 0; current_col < COLS_PER_HAND; current_col++) {
        // Select column by setting it low
        writePinLow(col_pins[current_col]);
        
        // Small delay for column to stabilize
        wait_us(30);
        
        // Read row pins
        for (uint8_t current_row = 0; current_row < ROWS_PER_HAND; current_row++) {
            // If pin reads low, key is pressed
            bool pressed = !readPin(row_pins[current_row]);
            matrix_row_t row_mask = ((matrix_row_t)1 << current_col);
            
            if (pressed) {
                raw_matrix[current_row] |= row_mask;
            } else {
                raw_matrix[current_row] &= ~row_mask;
            }
        }
        
        // Unselect column by setting it high
        writePinHigh(col_pins[current_col]);
    }
    
    // Debounce the matrix
    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);
    
    // Update battery level monitoring when running on battery
#ifdef BLUETOOTH_ENABLE
    if (current_mode == MATRIX_MODE_BT && timer_elapsed32(battery_timer) > BATTERY_CHECK_INTERVAL) {
        battery_level = board_get_battery_level();
        battery_timer = timer_read32();
    }
#endif

    // Check if matrix has changed for power saving feature
    matrix_has_changed = false;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (prev_matrix[i] != matrix[i]) {
            matrix_has_changed = true;
#ifdef MATRIX_POWER_SAVE
            matrix_timer = timer_read32();  // Reset power saving timer on any key press
#endif
        }
    }
    
    return matrix_has_changed;
}

/**
 * Read and return current matrix state.
 */
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

/**
 * Power management - prepare for sleep/suspend mode.
 */
void matrix_power_down(void) {
    // Prepare pins for low power mode
    for (uint8_t i = 0; i < ROWS_PER_HAND; i++) {
        setPinInputHigh(row_pins[i]);
    }
    
    for (uint8_t i = 0; i < COLS_PER_HAND; i++) {
        setPinInputHigh(col_pins[i]);
    }
    
#ifdef BLUETOOTH_ENABLE
    // Put Bluetooth into sleep mode
    bluetooth_sleep();
#endif
}

/**
 * Wake from sleep/suspend mode.
 */
void matrix_power_up(void) {
    // Reinitialize pins after waking
    for (uint8_t i = 0; i < COLS_PER_HAND; i++) {
        setPinOutput(col_pins[i]);
        writePinHigh(col_pins[i]);
    }
    
#ifdef BLUETOOTH_ENABLE
    // Wake Bluetooth from sleep mode
    bluetooth_wake();
#endif

#ifdef MATRIX_POWER_SAVE
    matrix_timer = timer_read32();
    matrix_power_saving = false;
#endif
}