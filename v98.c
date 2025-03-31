/*
 * This file is part of the QMK Firmware for Cidoo V98
 *
 * Copyright (c) 2023 QMK Community
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "v98.h"
#include "quantum.h"

// Define global variables for battery and connection state
static uint8_t battery_level = 100;
static uint32_t battery_timer = 0;
static bool charging_status = false;
static bool bt_connected = false;
static bool usb_connected = true;

// Keyboard initialization code
void keyboard_pre_init_kb(void) {
    // Initialize pins
    setPinOutput(LED_CAPS_LOCK_PIN);
    setPinOutput(LED_NUM_LOCK_PIN);
    setPinOutput(LED_SCROLL_LOCK_PIN);
    
    // Initialize bluetooth hardware if enabled
#ifdef BLUETOOTH_ENABLE
    // Set Bluetooth pins
    setPinOutput(B12); // BT_POWER
    setPinOutput(B11); // BT_RESET
    setPinInput(B10);  // BT_HOST_WAKE
    
    // Start with Bluetooth off if USB is connected
    palClearPad(GPIOB, GPIOB_BT_POWER);
#endif

    // Initialize battery monitoring
#ifdef BATTERY_ENABLE
    // Set up ADC for battery sensing
    palSetPadMode(GPIOA, GPIOA_BAT_SENSE, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA, GPIOA_BAT_CHARGE_DETECT, PAL_MODE_INPUT_PULLUP);
    
    // Initialize battery timer
    battery_timer = timer_read32();
#endif

    // Call the keyboard pre-init user code
    keyboard_pre_init_user();
}

// Keyboard post-initialization code
void keyboard_post_init_kb(void) {
    // Enable RGB LED if available
#ifdef RGBLIGHT_ENABLE
    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_BREATHING);
    rgblight_sethsv(HSV_BLUE);
#endif

    // Set initial LED states
    led_update_kb(host_keyboard_led_state());
    
    // Set rotary encoder default functionality
    encoder_init();
    
    // Call the keyboard post-init user code
    keyboard_post_init_user();
}

// Process keyboard-level keycodes
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // Update wake timer on any key press to prevent sleep
#ifdef MATRIX_POWER_SAVE
    if (record->event.pressed) {
        matrix_timer = timer_read32();
    }
#endif

    // Handle custom keycodes
    switch (keycode) {
        case KC_BLUETOOTH:
            if (record->event.pressed) {
                set_bluetooth_mode(!is_bluetooth_connected());
            }
            return false;
            
        case KC_BATTERY:
            if (record->event.pressed) {
                // Show battery level through RGB LED or other indicator
#ifdef RGBLIGHT_ENABLE
                uint8_t level = get_battery_level();
                if (level > 75) {
                    rgblight_sethsv_noeeprom(HSV_GREEN);
                } else if (level > 50) {
                    rgblight_sethsv_noeeprom(HSV_YELLOW);
                } else if (level > 25) {
                    rgblight_sethsv_noeeprom(HSV_ORANGE);
                } else {
                    rgblight_sethsv_noeeprom(HSV_RED);
                }
                // Return to normal after 2 seconds
                rgblight_timer_start(2000);
#endif
            }
            return false;
    }
    
    // Process user keycodes
    return process_record_user(keycode, record);
}

// LED update code
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        // Update LEDs
        writePin(LED_CAPS_LOCK_PIN, led_state.caps_lock);
        writePin(LED_NUM_LOCK_PIN, led_state.num_lock);
        writePin(LED_SCROLL_LOCK_PIN, led_state.scroll_lock);
    }
    return res;
}

// Rotary encoder update function
bool encoder_update_kb(bool clockwise) {
    // Default encoder behavior - media volume control
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    
    // Allow for user customization
    return encoder_update_user(clockwise);
}

// Called on every matrix scan
void matrix_scan_kb(void) {
    // Check battery level periodically
#ifdef BATTERY_ENABLE
    if (timer_elapsed32(battery_timer) > BATTERY_POLLING_INTERVAL) {
        battery_level = board_get_battery_level();
        charging_status = board_is_charging();
        battery_timer = timer_read32();
        
        // Handle low battery warning
        if (battery_level <= BATTERY_LOW_WARNING_LEVEL && !charging_status) {
#ifdef RGBLIGHT_ENABLE
            // Flash RGB LEDs for low battery warning
            rgblight_blink_fade_start(10, 30);
#endif
        }
        
        // Handle critical battery level
        if (battery_level <= BATTERY_CRITICAL_LEVEL && !charging_status) {
            // Enter deep power saving mode
#ifdef RGBLIGHT_ENABLE
            rgblight_disable_noeeprom();
#endif
            // Reduce matrix scan rate dramatically
            matrix_power_saving = true;
        }
    }
#endif

    // Handle connection state changes
#ifdef BLUETOOTH_ENABLE
    // Check if USB was connected but is now disconnected
    if (usb_connected && USB_DeviceState != DEVICE_STATE_Configured) {
        usb_connected = false;
        set_bluetooth_mode(true);
    }
    // Check if USB was disconnected but is now connected
    else if (!usb_connected && USB_DeviceState == DEVICE_STATE_Configured) {
        usb_connected = true;
        set_bluetooth_mode(false);
    }
#endif

    // Call user matrix scan function
    matrix_scan_user();
}

// Function to get battery level
uint8_t get_battery_level(void) {
    return battery_level;
}

// Function to check if battery is charging
bool is_charging(void) {
    return charging_status;
}

// Function to check if Bluetooth is connected
bool is_bluetooth_connected(void) {
    return bt_connected;
}

// Function to check if USB is connected
bool is_usb_connected(void) {
    return usb_connected;
}

// Function to switch between Bluetooth and USB modes
void set_bluetooth_mode(bool enable) {
#ifdef BLUETOOTH_ENABLE
    if (enable) {
        // Turn on Bluetooth module
        palSetPad(GPIOB, GPIOB_BT_POWER);
        palSetPad(GPIOB, GPIOB_BT_RESET);
        wait_ms(100);
        palClearPad(GPIOB, GPIOB_BT_RESET);
        wait_ms(100);
        bt_connected = true;
        
#ifdef RGBLIGHT_ENABLE
        // Indicate Bluetooth mode with blue color
        rgblight_sethsv_noeeprom(HSV_BLUE);
#endif
    } else {
        // Turn off Bluetooth module to save power
        palClearPad(GPIOB, GPIOB_BT_POWER);
        bt_connected = false;
        
#ifdef RGBLIGHT_ENABLE
        // Indicate USB mode with cyan color
        rgblight_sethsv_noeeprom(HSV_CYAN);
#endif
    }
#endif
}

// Function called when device enters suspend mode
void suspend_power_down_kb(void) {
    // Turn off LEDs to save power
#ifdef RGBLIGHT_ENABLE
    rgblight_disable_noeeprom();
#endif
    
    // Put Bluetooth module into sleep mode if active
#ifdef BLUETOOTH_ENABLE
    if (bt_connected) {
        // Send sleep command to Bluetooth module
        // The exact implementation depends on the specific Bluetooth module
    }
#endif
    
    // Call