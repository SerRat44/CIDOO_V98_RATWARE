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

// Connection states
typedef enum {
    BT_DISCONNECTED = 0,
    BT_CONNECTING,
    BT_CONNECTED,
    BT_PAIRED,
    BT_SLEEP
} bluetooth_state_t;

// Connection modes
typedef enum {
    BT_MODE_OFF = 0,
    BT_MODE_ON,
    BT_MODE_PAIR
} bluetooth_mode_t;

// Bluetooth device functions
void bluetooth_init(void);
void bluetooth_task(void);
void bluetooth_mode_enable(void);
void bluetooth_mode_disable(void);
void bluetooth_connection_update(void);
void bluetooth_mode_pairing(void);
void bluetooth_sleep(void);
void bluetooth_wake(void);
void bluetooth_send_battery_level(uint8_t level);

// Bluetooth state functions
bluetooth_state_t bluetooth_get_state(void);
bluetooth_mode_t bluetooth_get_mode(void);
bool bluetooth_is_connected(void);
uint8_t bluetooth_get_profile(void);
void bluetooth_switch_profile(uint8_t profile);

// HID report functions for Bluetooth
void bluetooth_send_keyboard(uint8_t *report);
void bluetooth_send_mouse(uint8_t *report);
void bluetooth_send_system(uint16_t data);
void bluetooth_send_consumer(uint16_t data);

// Power management functions
void bluetooth_power_save_enable(void);
void bluetooth_power_save_disable(void);

// Handler for Bluetooth UART communication
void bluetooth_uart_task(void);
void bluetooth_uart_receive(uint8_t c);

// Configuration functions
bool bluetooth_load_config(void);
bool bluetooth_save_config(void);

// Advanced features that may be supported
#ifdef BLUETOOTH_ADV_FEATURES
bool bluetooth_device_scan_start(void);
bool bluetooth_device_scan_stop(void);
void bluetooth_device_list_clear(void);
bool bluetooth_device_connect(uint8_t *addr);
bool bluetooth_device_disconnect(void);
bool bluetooth_device_forget(uint8_t *addr);
#endif

// External variables for bluetooth state
extern bluetooth_state_t bluetooth_state;
extern bluetooth_mode_t bluetooth_mode;
extern uint8_t bluetooth_profile;
extern bool bluetooth_initialized;
extern bool bluetooth_power_save_on;