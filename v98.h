/*
 * This file is part of the QMK Firmware for Cidoo V98
 *
 * Copyright (c) 2023 QMK Community
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "quantum.h"

// Encoder position between k0M and k0O
// We'll add a new key position k0N for the encoder click
#define LAYOUT_cidoo_v98(                                                                           \
    k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I, k0J, k0K, k0L, k0M, k0N, k0O, k0P, k0Q, k0R,      \
    k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I, k1J, k1K, k1L, k1M, k1N, k1O, k1P, k1Q, k1R,      \
    k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I, k2J, k2K, k2L, k2M, k2N, k2O, k2P, k2Q, k2R,      \
    k3A, k3B, k3C, k3D, k3E, k3F, k3G, k3H, k3I, k3J, k3K, k3L,      k3N, k3O, k3P, k3Q,           \
    k4A,      k4C, k4D, k4E, k4F, k4G, k4H, k4I, k4J, k4K, k4L, k4M, k4N, k4O, k4P, k4Q, k4R,      \
    k5A, k5B, k5C,           k5F,                k5I, k5J, k5K, k5M, k5N, k5O, k5P, k5Q            \
) {                                                                                                  \
    { k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I, k0J, k0K, k0L, k0M, k0N, k0O, k0P, k0Q, k0R },  \
    { k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I, k1J, k1K, k1L, k1M, k1N, k1O, k1P, k1Q, k1R },  \
    { k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I, k2J, k2K, k2L, k2M, k2N, k2O, k2P, k2Q, k2R },  \
    { k3A, k3B, k3C, k3D, k3E, k3F, k3G, k3H, k3I, k3J, k3K, k3L, KC_NO, k3N, k3O, k3P, k3Q, KC_NO }, \
    { k4A, KC_NO, k4C, k4D, k4E, k4F, k4G, k4H, k4I, k4J, k4K, k4L, k4M, k4N, k4O, k4P, k4Q, k4R }, \
    { k5A, k5B, k5C, KC_NO, KC_NO, k5F, KC_NO, KC_NO, k5I, k5J, k5K, KC_NO, k5M, k5N, k5O, k5P, k5Q, KC_NO } \
}

// Define encoder callback function declarations
void encoder_update_kb(bool clockwise);
void encoder_update_user(bool clockwise);

// Define battery status functions
uint8_t get_battery_level(void);
bool is_charging(void);

// Define Bluetooth/USB connection mode functions
bool is_bluetooth_connected(void);
bool is_usb_connected(void);
void set_bluetooth_mode(bool enable);