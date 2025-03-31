/*
 * This file is part of the QMK Firmware for Cidoo V98
 *
 * Copyright (c) 2023 QMK Community
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "encoder.h"
#include "v98.h"
#include "timer.h"
#include "quantum.h"
#include "debug.h"
#include "gpio.h"

// Define pins for encoder
#ifndef ENCODERS_PAD_A
#define ENCODERS_PAD_A { A4 }
#endif
#ifndef ENCODERS_PAD_B
#define ENCODERS_PAD_B { A3 }
#endif

// Pin for the encoder press button
#ifndef ENCODERS_SWITCH_PIN
#define ENCODERS_SWITCH_PIN { A2 }
#endif

// Define array of encoder pins
static const pin_t encoders_pad_a[MAX_ENCODERS] = ENCODERS_PAD_A;
static const pin_t encoders_pad_b[MAX_ENCODERS] = ENCODERS_PAD_B;
static const pin_t encoders_switch_pin[MAX_ENCODERS] = ENCODERS_SWITCH_PIN;

// Encoder state arrays
static uint8_t encoder_state[MAX_ENCODERS] = {0};
static int8_t encoder_pulses[MAX_ENCODERS] = {0};
static bool encoder_switch_state[MAX_ENCODERS] = {false};
static bool encoder_switch_pressed[MAX_ENCODERS] = {false};

// Global encoder state
encoder_state_t encoder_states[MAX_ENCODERS] = {{0}};
encoder_mode_t encoder_mode = ENC_MODE_VOLUME;
bool encoder_acceleration_enabled = true;

// Timer for encoder updates
static uint32_t encoder_timer = 0;
#define ENCODER_TASK_INTERVAL 20 // 20ms

// Timer for encoder press debounce
static uint32_t encoder_press_timer[MAX_ENCODERS] = {0};
#define ENCODER_PRESS_DEBOUNCE 20 // 20ms

// For tracking encoder matrix position
static bool encoder_in_keymatrix = true;
static uint8_t encoder_press_row = 0;
static uint8_t encoder_press_col = 13; // Position between k0M and k0O

/**
 * Initialize encoder hardware.
 */
void encoder_init(void) {
    // Initialize encoder pins
    for (uint8_t i = 0; i < MAX_ENCODERS; i++) {
        setPinInputHigh(encoders_pad_a[i]);
        setPinInputHigh(encoders_pad_b[i]);
        
        // Initialize encoder switch pin
        setPinInputHigh(encoders_switch_pin[i]);
        
        // Initialize state
        encoder_states[i].direction = 0;
        encoder_states[i].position = 0;
        encoder_states[i].velocity = 0;
        encoder_states[i].last_update_time = timer_read32();
    }
    
    // Initialize timer
    encoder_timer = timer_read32();
    
    // Call custom initializations
    encoder_init_kb();
}

/**
 * Read encoder hardware state
 */
void encoder_read(void) {
    for (uint8_t i = 0; i < MAX_ENCODERS; i++) {
        // Read encoder pins
        uint8_t new_state = (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
        
        // Process state change using look-up table
        static const int8_t encoder_lut[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
        int8_t pulse = encoder_lut[(encoder_state[i] << 2) | new_state];
        
        if (pulse != 0) {
            encoder_pulses[i] += pulse;
            
            // Update position
            encoder_states[i].position += pulse;
            
            // Update direction (for velocity calculation)
            encoder_states[i].direction = pulse;
            
            // Update velocity
            encoder_velocity_update(i);
        }
        
        // Update state
        encoder_state[i] = new_state;
        
        // Read encoder switch
        bool new_switch_state = !readPin(encoders_switch_pin[i]);
        
        // Debounce switch
        if (new_switch_state != encoder_switch_state[i]) {
            if (timer_elapsed32(encoder_press_timer[i]) > ENCODER_PRESS_DEBOUNCE) {
                encoder_switch_state[i] = new_switch_state;
                encoder_press_timer[i] = timer_read32();
                
                // Track press state for matrix
                if (new_switch_state) {
                    encoder_switch_pressed[i] = true;
                    
                    // If encoder press is mapped directly to matrix
                    if (encoder_in_keymatrix) {
                        // Simulate keypress in matrix
                        // NOTE: This direct matrix manipulation is not ideal
                        // but allows us to leverage existing keymap for encoder press
                        dprintf("Encoder press detected\n");
                    }
                }
            }
        }
    }
}

/**
 * Update encoder state and process actions
 */
void encoder_state_update(void) {
    for (uint8_t i = 0; i < MAX_ENCODERS; i++) {
        // Process rotation
        while (encoder_pulses[i] >= ENCODER_RESOLUTION) {
            encoder_pulses[i] -= ENCODER_RESOLUTION;
            encoder_action(i, true); // Clockwise
        }
        while (encoder_pulses[i] <= -ENCODER_RESOLUTION) {
            encoder_pulses[i] += ENCODER_RESOLUTION;
            encoder_action(i, false); // Counter-clockwise
        }
    }
}

/**
 * Main encoder task, called periodically
 */
void encoder_task(void) {
    // Only run task at defined interval
    if (timer_elapsed32(encoder_timer) < ENCODER_TASK_INTERVAL) {
        return;
    }
    
    encoder_timer = timer_read32();
    
    // Read encoder hardware
    encoder_read();
    
    // Update encoder state and process actions
    encoder_state_update();