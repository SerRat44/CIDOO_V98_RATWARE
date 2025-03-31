/*
 * This file is part of the QMK Firmware for Cidoo V98
 *
 * Copyright (c) 2023 QMK Community
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

/*
 * Board identifier
 */
#define BOARD_CIDOO_V98
#define BOARD_NAME                  "CIDOO V98"

/*
 * Board oscillators-related settings
 */
#define STM32_LSECLK                0U
#define STM32_LSEDRV                (3U << 3U)
#define STM32_HSECLK                8000000U

/*
 * Board voltages
 * Required for performance limits calculation
 */
#define STM32_VDD                   330U

/*
 * MCU type as defined in the ST header
 */
#define STM32F103xB

/*
 * I/O ports initial setup
 * PIN state at power-on and during active mode
 */
#define GPIOA_LED                   1U
#define GPIOB_USB_DISCONNECT        9U

// Battery management pins
#define GPIOA_BAT_SENSE             2U
#define GPIOA_BAT_CHARGE_DETECT     3U

// Bluetooth control pins
#define GPIOB_BT_POWER              12U
#define GPIOB_BT_RESET              11U
#define GPIOB_BT_HOST_WAKE          10U
#define GPIOB_BT_TX                 6U
#define GPIOB_BT_RX                 7U

// Rotary encoder pins
#define GPIOA_ENC_A                 5U
#define GPIOA_ENC_B                 6U
#define GPIOA_ENC_PRESS             7U

// Matrix scanning pins setup
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_ENC_A) |           \
                                     PIN_MODE_INPUT(GPIOA_ENC_B) |           \
                                     PIN_MODE_INPUT(GPIOA_ENC_PRESS) |       \
                                     PIN_MODE_OUTPUT(GPIOA_LED) |            \
                                     PIN_MODE_INPUT(GPIOA_BAT_SENSE) |       \
                                     PIN_MODE_INPUT(GPIOA_BAT_CHARGE_DETECT))

#define VAL_GPIOB_MODER             (PIN_MODE_OUTPUT(GPIOB_USB_DISCONNECT) | \
                                     PIN_MODE_OUTPUT(GPIOB_BT_POWER) |       \
                                     PIN_MODE_OUTPUT(GPIOB_BT_RESET) |       \
                                     PIN_MODE_INPUT(GPIOB_BT_HOST_WAKE) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_BT_TX) |       \
                                     PIN_MODE_ALTERNATE(GPIOB_BT_RX))

// Port A pullup/pulldown settings
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_PULLUP(GPIOA_ENC_A) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_ENC_B) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_ENC_PRESS))

// Port B pullup/pulldown settings
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLUP(GPIOB_BT_HOST_WAKE))

/*
 * USB Bus setup
 */
#define BOARD_USB_DISCONNECTION     1