/*
 * This file is part of the QMK Firmware for Cidoo V98
 *
 * Copyright (c) 2023 QMK Community
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "quantum.h"

// Encoder resolution - ticks per detent
#define ENCODER_RESOLUTION 4

// Maximum number of encoders supported
#define MAX_ENCODERS 1

// Structure to track encoder state
typedef struct {
    int8_t  direction;
    uint8_t position;
    int16_t velocity;
    uint32_t last_update_time;
} encoder_state_t;

// Encoder operation modes
typedef enum {
    ENC_MODE_VOLUME,       // Default mode: Volume control
    ENC_MODE_BRIGHTNESS,   // Display brightness
    ENC_MODE_MEDIA,        // Media control (prev/next)
    ENC_MODE_SCROLL,       // Scrolling
    ENC_MODE_CUSTOM,       // Custom function defined by user
    ENC_MODE_RGB,          // RGB control
    ENC_MODE_COUNT         // Number of modes (always keep last)
} encoder_mode_t;

// Function prototypes
void encoder_init(void);
void encoder_read(void);
void encoder_state_update(void);
void encoder_task(void);
void encoder_set_mode(encoder_mode_t mode);
encoder_mode_t encoder_get_mode(void);
void encoder_action(uint8_t index, bool clockwise);
void encoder_custom_action(uint8_t index, bool clockwise);
void encoder_layer_action(uint8_t index, bool clockwise, uint8_t layer);

// Matrix position functions (for encoder press)
bool encoder_press_is_pressed(void);
void encoder_press_update(void);

// Advanced encoder features
void encoder_velocity_update(uint8_t index);
int16_t encoder_get_velocity(uint8_t index);
void encoder_set_acceleration(bool enable);
bool encoder_get_acceleration(void);

// Initialization for specific implementations
void encoder_init_kb(void);
void encoder_init_user(void);

// Callback functions
bool encoder_update_kb(uint8_t index, bool clockwise);
bool encoder_update_user(uint8_t index, bool clockwise);

// For per-layer encoder functionality
bool encoder_update_layer(uint8_t index, bool clockwise, uint8_t layer);

// External variables
extern encoder_state_t encoder_state[MAX_ENCODERS];
extern encoder_mode_t encoder_mode;
extern bool encoder_acceleration_enabled;

// Encoder mapping (if enabled)
#ifdef ENCODER_MAP_ENABLE
uint16_t encoder_get_keycode(uint8_t encoder_idx, bool clockwise, uint8_t layer);
#endif