/*
 * This file is part of the QMK Firmware for Cidoo V98
 *
 * Copyright (c) 2023 QMK Community
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "bluetooth.h"
#include "quantum.h"
#include "v98.h"
#include "debug.h"
#include "timer.h"
#include "wait.h"
#include "ch.h"
#include "hal.h"

// Define pins for Bluetooth module
#define BT_POWER_PIN B12
#define BT_RESET_PIN B11
#define BT_HOST_WAKE_PIN B10
#define BT_UART_TX B6
#define BT_UART_RX B7

// UART driver configuration
static const SerialConfig bt_serial_config = {
    115200,                                      // 115200 baud
    0,                                          // CR1 register value
    USART_CR2_STOP1_BITS,                      // CR2 register value
    0                                           // CR3 register value
};

// Bluetooth state and mode variables
bluetooth_state_t bluetooth_state = BT_DISCONNECTED;
bluetooth_mode_t bluetooth_mode = BT_MODE_OFF;
uint8_t bluetooth_profile = 0;
bool bluetooth_initialized = false;
bool bluetooth_power_save_on = false;

// Buffer for UART communication
#define BT_BUFFER_SIZE 64
static uint8_t bt_buffer[BT_BUFFER_SIZE];
static uint8_t bt_buffer_pos = 0;

// Timer for Bluetooth task execution
static uint32_t bt_timer = 0;
#define BT_TASK_INTERVAL 100 // 100ms

// Bluetooth command sequences
static const uint8_t BT_CMD_INIT[] = { 0xAA, 0x55, 0x01, 0x01 };
static const uint8_t BT_CMD_SLEEP[] = { 0xAA, 0x55, 0x03, 0x01 };
static const uint8_t BT_CMD_WAKE[] = { 0xAA, 0x55, 0x03, 0x00 };
static const uint8_t BT_CMD_PAIR[] = { 0xAA, 0x55, 0x02, 0x01 };
static const uint8_t BT_CMD_UNPAIR[] = { 0xAA, 0x55, 0x02, 0x00 };
static const uint8_t BT_CMD_SWITCH_PROFILE[] = { 0xAA, 0x55, 0x04 };
static const uint8_t BT_CMD_BATTERY[] = { 0xAA, 0x55, 0x05 };

// Forward declaration of internal functions
static void bluetooth_send_cmd(const uint8_t *cmd, uint8_t len);
static void bluetooth_process_response(uint8_t *data, uint8_t len);
static void bluetooth_reset(void);

/* Initialize the Bluetooth module */
void bluetooth_init(void) {
    if (bluetooth_initialized) {
        return;
    }

    // Configure pins
    setPinOutput(BT_POWER_PIN);
    setPinOutput(BT_RESET_PIN);
    setPinInput(BT_HOST_WAKE_PIN);
    
    // Start with Bluetooth module powered off
    writePinLow(BT_POWER_PIN);
    writePinLow(BT_RESET_PIN);
    
    // Initialize UART for Bluetooth communication
    palSetPadMode(GPIOB, BT_UART_TX, PAL_MODE_ALTERNATE(7));  // UART TX
    palSetPadMode(GPIOB, BT_UART_RX, PAL_MODE_ALTERNATE(7));  // UART RX
    
    sdStart(&SD3, &bt_serial_config);
    
    // Initialize buffer
    for (int i = 0; i < BT_BUFFER_SIZE; i++) {
        bt_buffer[i] = 0;
    }
    bt_buffer_pos = 0;
    
    // Initialize timer
    bt_timer = timer_read32();
    
    // Set initial state
    bluetooth_state = BT_DISCONNECTED;
    bluetooth_mode = BT_MODE_OFF;
    bluetooth_profile = 0;
    
    // Load saved configuration
    bluetooth_load_config();
    
    bluetooth_initialized = true;
    
    // Log initialization
    dprintf("Bluetooth initialized\n");
}

/* Enable Bluetooth mode */
void bluetooth_mode_enable(void) {
    if (bluetooth_mode == BT_MODE_ON) {
        return;
    }
    
    dprintf("Bluetooth: enabling\n");
    
    // Power on the module
    writePinHigh(BT_POWER_PIN);
    wait_ms(100);
    
    // Reset the module
    bluetooth_reset();
    
    // Set mode to on
    bluetooth_mode = BT_MODE_ON;
    
    // Send initialization command
    bluetooth_send_cmd(BT_CMD_INIT, sizeof(BT_CMD_INIT));
    
    // Update LED to indicate Bluetooth mode
#ifdef RGBLIGHT_ENABLE
    rgblight_sethsv_noeeprom(HSV_BLUE);
#endif
}

/* Disable Bluetooth mode */
void bluetooth_mode_disable(void) {
    if (bluetooth_mode == BT_MODE_OFF) {
        return;
    }
    
    dprintf("Bluetooth: disabling\n");
    
    // Power off the module
    writePinLow(BT_POWER_PIN);
    
    // Set mode to off
    bluetooth_mode = BT_MODE_OFF;
    bluetooth_state = BT_DISCONNECTED;
    
    // Update LED to indicate USB mode
#ifdef RGBLIGHT_ENABLE
    rgblight_sethsv_noeeprom(HSV_CYAN);
#endif
}

/* Put Bluetooth into pairing mode */
void bluetooth_mode_pairing(void) {
    if (bluetooth_mode != BT_MODE_ON) {
        bluetooth_mode_enable();
    }
    
    dprintf("Bluetooth: enter pairing mode\n");
    
    // Send pairing command
    bluetooth_send_cmd(BT_CMD_PAIR, sizeof(BT_CMD_PAIR));
    
    // Update mode
    bluetooth_mode = BT_MODE_PAIR;
    
    // Visual indication of pairing mode
#ifdef RGBLIGHT_ENABLE
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 2);
#endif
}

/* Update Bluetooth connection state */
void bluetooth_connection_update(void) {
    // Check connection state through HOST_WAKE pin
    bool connected = readPin(BT_HOST_WAKE_PIN);
    
    if (connected && bluetooth_state != BT_CONNECTED && bluetooth_state != BT_PAIRED) {
        dprintf("Bluetooth: connected\n");
        bluetooth_state = BT_CONNECTED;
        
        // Update LED
#ifdef RGBLIGHT_ENABLE
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
#endif
    } else if (!connected && (bluetooth_state == BT_CONNECTED || bluetooth_state == BT_PAIRED)) {
        dprintf("Bluetooth: disconnected\n");
        bluetooth_state = BT_DISCONNECTED;
        
        // Update LED
#ifdef RGBLIGHT_ENABLE
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 1);
#endif
    }
}

/* Put Bluetooth module to sleep */
void bluetooth_sleep(void) {
    if (bluetooth_mode != BT_MODE_ON || bluetooth_state == BT_SLEEP) {
        return;
    }
    
    dprintf("Bluetooth: sleep\n");
    
    // Send sleep command
    bluetooth_send_cmd(BT_CMD_SLEEP, sizeof(BT_CMD_SLEEP));
    
    // Update state
    bluetooth_state = BT_SLEEP;
}

/* Wake Bluetooth module from sleep */
void bluetooth_wake(void) {
    if (bluetooth_mode != BT_MODE_ON || bluetooth_state != BT_SLEEP) {
        return;
    }
    
    dprintf("Bluetooth: wake\n");
    
    // Send wake command
    bluetooth_send_cmd(BT_CMD_WAKE, sizeof(BT_CMD_WAKE));
    
    // Update state
    bluetooth_state = BT_DISCONNECTED;
    
    // Check connection
    bluetooth_connection_update();
}

/* Send battery level to connected device */
void bluetooth_send_battery_level(uint8_t level) {
    if (bluetooth_mode != BT_MODE_ON || !bluetooth_is_connected()) {
        return;
    }
    
    // Prepare battery command
    uint8_t cmd[5];
    memcpy(cmd, BT_CMD_BATTERY, 3);
    cmd[3] = level;
    cmd[4] = 0; // 0 = not charging, 1 = charging
    
    // Send command
    bluetooth_send_cmd(cmd, 5);
}

/* Get current Bluetooth state */
bluetooth_state_t bluetooth_get_state(void) {
    return bluetooth_state;
}

/* Get current Bluetooth mode */
bluetooth_mode_t bluetooth_get_mode(void) {
    return bluetooth_mode;
}

/* Check if Bluetooth is connected */
bool bluetooth_is_connected(void) {
    return (bluetooth_state == BT_CONNECTED || bluetooth_state == BT_PAIRED);
}

/* Get current Bluetooth profile */
uint8_t bluetooth_get_profile(void) {
    return bluetooth_profile;
}

/* Switch to different Bluetooth profile (for multi-device support) */
void bluetooth_switch_profile(uint8_t profile) {
    if (bluetooth_mode != BT_MODE_ON) {
        return;
    }
    
    if (profile > 3) {
        profile = 0;
    }
    
    dprintf("Bluetooth: switch to profile %d\n", profile);
    
    // Prepare profile switch command
    uint8_t cmd[4];
    memcpy(cmd, BT_CMD_SWITCH_PROFILE, 3);
    cmd[3] = profile;
    
    // Send command
    bluetooth_send_cmd(cmd, 4);
    
    // Update profile
    bluetooth_profile = profile;
    
    // Visual feedback
#ifdef RGBLIGHT_ENABLE
    // Flash RGB to indicate profile change
    uint8_t hue = 42 * profile; // Different color for each profile
    rgblight_sethsv_noeeprom(hue, 255, 255);
    wait_ms(200);
    rgblight_sethsv_noeeprom(HSV_BLUE);
#endif
}

/* Enable Bluetooth power saving mode */
void bluetooth_power_save_enable(void) {
    if (bluetooth_power_save_on) {
        return;
    }
    
    dprintf("Bluetooth: power save enabled\n");
    
    // TODO: Implement Bluetooth specific power saving
    
    bluetooth_power_save_on = true;
}

/* Disable Bluetooth power saving mode */
void bluetooth_power_save_disable(void) {
    if (!bluetooth_power_save_on) {
        return;
    }
    
    dprintf("Bluetooth: power save disabled\n");
    
    // TODO: Disable power saving
    
    bluetooth_power_save_on = false;
}

/* Send keyboard report over Bluetooth */
void bluetooth_send_keyboard(uint8_t *report) {
    if (bluetooth_mode != BT_MODE_ON || !bluetooth_is_connected()) {
        return;
    }
    
    // Format and send HID report
    // Implementation depends on specific Bluetooth module
}

/* Send mouse report over Bluetooth */
void bluetooth_send_mouse(uint8_t *report) {
    if (bluetooth_mode != BT_MODE_ON || !bluetooth_is_connected()) {
        return;
    }
    
    // Format and send HID report
    // Implementation depends on specific Bluetooth module
}

/* Send system report over Bluetooth */
void bluetooth_send_system(uint16_t data) {
    if (bluetooth_mode != BT_MODE_ON || !bluetooth_is_connected()) {
        return;
    }
    
    // Format and send HID report
    // Implementation depends on specific Bluetooth module
}

/* Send consumer report over Bluetooth */
void bluetooth_send_consumer(uint16_t data) {
    if (bluetooth_mode != BT_MODE_ON || !bluetooth_is_connected()) {
        return;
    }
    
    // Format and send HID report
    // Implementation depends on specific Bluetooth module
}

/* Bluetooth task - called periodically */
void bluetooth_task(void) {
    // Only run task at defined interval
    if (timer_elapsed32(bt_timer) < BT_TASK_INTERVAL) {
        return;
    }
    
    bt_timer = timer_read32();
    
    // Check if Bluetooth is enabled
    if (bluetooth_mode == BT_MODE_OFF) {
        return;
    }
    
    // Update connection state
    bluetooth_connection_update();
    
    // Process UART data
    bluetooth_uart_task();
}

/* Process UART data from Bluetooth module */
void bluetooth_uart_task(void) {
    // Check for available data from the Bluetooth module
    while (sdGetTimeout(&SD3, TIME_IMMEDIATE) != MSG_TIMEOUT) {
        uint8_t c = sdGet(&SD3);
        bluetooth_uart_receive(c);
    }
}

/* Handle received byte from UART */
void bluetooth_uart_receive(uint8_t c) {
    // Add byte to buffer
    if (bt_buffer_pos < BT_BUFFER_SIZE) {
        bt_buffer[bt_buffer_pos++] = c;
    }
    
    // Check if we have a complete command (0xAA, 0x55, ...)
    if (bt_buffer_pos >= 2 && bt_buffer[0] == 0xAA && bt_buffer[1] == 0x55) {
        // Check if we have command length (usually byte 3)
        if (bt_buffer_pos >= 3) {
            uint8_t cmd_len = bt_buffer[2];
            
            // If we have the full command, process it
            if (bt_buffer_pos >= cmd_len + 3) {
                bluetooth_process_response(bt_buffer, bt_buffer_pos);
                
                // Reset buffer
                bt_buffer_pos = 0;
            }
        }
    } else if (bt_buffer_pos >= 2 && (bt_buffer[0] != 0xAA || bt_buffer[1] != 0x55)) {
        // Invalid command start, reset buffer
        bt_buffer_pos = 0;
    }
}

/* Process response from Bluetooth module */
static void bluetooth_process_response(uint8_t *data, uint8_t len) {
    if (len < 4) {
        return;
    }
    
    // Process based on command type (byte 3)
    switch (data[2]) {
        case 0x01: // Init response
            dprintf("Bluetooth: init response\n");
            break;
            
        case 0x02: // Pairing response
            if (data[3] == 0x00) {
                dprintf("Bluetooth: pairing completed\n");
                bluetooth_mode = BT_MODE_ON;
                bluetooth_state = BT_PAIRED;
            } else {
                dprintf("Bluetooth: pairing failed\n");
            }
            break;
            
        case 0x03: // Sleep/wake response
            if (data[3] == 0x00) {
                dprintf("Bluetooth: wake response\n");
            } else {
                dprintf("Bluetooth: sleep response\n");
            }
            break;
            
        case 0x04: // Profile switch response
            dprintf("Bluetooth: profile switch response\n");
            break;
            
        case 0x80: // Connection status update
            if (data[3] == 0x01) {
                dprintf("Bluetooth: connected notification\n");
                bluetooth_state = BT_CONNECTED;
            } else {
                dprintf("Bluetooth: disconnected notification\n");
                bluetooth_state = BT_DISCONNECTED;
            }
            break;
            
        default:
            dprintf("Bluetooth: unknown response %02X\n", data[2]);
            break;
    }
}

/* Send command to Bluetooth module */
static void bluetooth_send_cmd(const uint8_t *cmd, uint8_t len) {
    for (uint8_t i = 0; i < len; i++) {
        sdPut(&SD3, cmd[i]);
    }
}

/* Reset Bluetooth module */
static void bluetooth_reset(void) {
    dprintf("Bluetooth: reset\n");
    
    // Reset sequence
    writePinLow(BT_RESET_PIN);
    wait_ms(100);
    writePinHigh(BT_RESET_PIN);
    wait_ms(100);
}

/* Load Bluetooth configuration from EEPROM */
bool bluetooth_load_config(void) {
    // Implementation depends on how you want to store settings
    // Example placeholder
    return true;
}

/* Save Bluetooth configuration to EEPROM */
bool bluetooth_save_config(void) {
    // Implementation depends on how you want to store settings
    // Example placeholder
    return true;
}