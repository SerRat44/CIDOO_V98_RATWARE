/*
 * This file is part of the QMK Firmware for Cidoo V98
 *
 * Copyright (c) 2023 QMK Community
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

/* USB Device descriptor parameters */
#define VENDOR_ID       0xCDFF  // Cidoo
#define PRODUCT_ID      0x9801  // V98 Keyboard
#define DEVICE_VER      0x0001  // Revision 1
#define MANUFACTURER    "Cidoo"
#define PRODUCT         "V98"

/* Key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 18

/* Key matrix pins */
#define MATRIX_ROW_PINS { B10, B1, B0, A7, A6, A5 }
#define MATRIX_COL_PINS { B12, B13, B14, B15, A8, A9, A10, A15, B3, B4, B5, B6, B7, B8, B9, C13, C14, C15 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Encoder Configuration */
#define ENCODERS_PAD_A { A4 }
#define ENCODERS_PAD_B { A3 }
#define ENCODER_RESOLUTION 4
#define ENCODER_DEFAULT_POS 0

// Enable the encoder press as a key
#define ENCODERS_SWITCH_PIN { A2 }

/* RGB Underglow / WS2812 LED Configuration */
#define RGB_DI_PIN A1
#define RGBLED_NUM 21
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP  // Turn off LEDs when host sleeps for power saving

/* RGB Effects */
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE

/* Bluetooth Configuration */
#define BLUETOOTH_ENABLE
#define BLUETOOTH_DRIVER BLUETOOTH_QMK
#define BLUETOOTH_EXTENSIONS

/* Battery Configuration */
#define BATTERY_POLLING_INTERVAL 30000  // 30 seconds
#define BATTERY_LOW_WARNING_LEVEL 20    // 20% battery warning
#define BATTERY_CRITICAL_LEVEL 10       // 10% critical level

/* Power Saving */
#define MATRIX_POWER_SAVE
#define MATRIX_POWER_SAVE_TIMEOUT 300000  // 5 minutes
#define USB_SUSPEND_WAKEUP_DELAY 200

/* Bootmagic Lite key: Hold ESC on power-up */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

/* EEPROM for VIA */
#define DYNAMIC_KEYMAP_LAYER_COUNT 4
#define EEPROM_MAGIC 0x9852
#define EEPROM_VERSION 1
#define DYNAMIC_KEYMAP_MACRO_COUNT 16

/* Tap-hold configuration */
#define TAPPING_TERM 200
#define TAPPING_TOGGLE 2
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT

/* Enable additional features */
#define LAYER_STATE_16BIT

/* Disable unused features to save space */
#define NO_DEBUG
#define NO_PRINT