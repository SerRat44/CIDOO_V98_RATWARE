/*
 * This file is part of the QMK Firmware for Cidoo V98
 *
 * Copyright (c) 2023 QMK Community
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

/**
 * @file    halconf.h
 * @brief   HAL configuration for STM32F103.
 * @details HAL configuration file, containing various settings for
 *          the STM32F103 Hardware Abstraction Layer.
 */

#pragma once

#define HAL_USE_PAL                 TRUE
#define HAL_USE_GPT                 TRUE    // Required for RGB effects
#define HAL_USE_I2C                 TRUE    // For future I2C accessories
#define HAL_USE_PWM                 TRUE    // For LED control
#define HAL_USE_SERIAL              TRUE    // For Bluetooth UART
#define HAL_USE_SPI                 FALSE
#define HAL_USE_ADC                 TRUE    // For battery monitoring
#define HAL_USE_EXT                 TRUE    // For external interrupts (encoder)
#define HAL_USE_USB                 TRUE    // For USB connectivity
#define HAL_USE_RTC                 TRUE    // For timekeeping
#define HAL_USE_WDG                 FALSE
#define HAL_USE_IWDG                FALSE

/* PAL driver system settings */
#define PAL_USE_CALLBACKS           TRUE
#define PAL_USE_WAIT                TRUE

/* EXT driver system settings */
#define EXT_USE_CHANNELS            TRUE
#define EXT_CHANNELS_POLARITY       0x00000000
#define EXT_MAX_CHANNELS            16

/* Serial driver system settings */
#define SERIAL_DEFAULT_BITRATE      115200  // Bluetooth default baud rate
#define SERIAL_BUFFERS_SIZE         64
#define SERIAL_USE_INTERRUPTS       TRUE

/* USB driver system settings */
#define USB_USE_WAIT                TRUE
#define USB_USE_MUTUAL_EXCLUSION    FALSE   // No need for USB mutex

/* ADC driver system settings - for battery monitoring */
#define ADC_USE_WAIT                TRUE
#define ADC_USE_MUTUAL_EXCLUSION    FALSE
#define STM32_ADC_USE_ADC1          TRUE
#define STM32_ADC_ADC1_DMA_PRIORITY 2
#define STM32_ADC_ADC1_IRQ_PRIORITY 5

/* I2C driver system settings - high priority for display interface */
#define I2C_USE_MUTUAL_EXCLUSION    TRUE
#define STM32_I2C_USE_I2C1          TRUE
#define STM32_I2C_USE_I2C2          FALSE
#define STM32_I2C_I2C1_IRQ_PRIORITY 4
#define STM32_I2C_USE_DMA           TRUE
#define STM32_I2C_I2C1_DMA_PRIORITY 3

/* PWM driver system settings - for LED control */
#define PWM_USE_TIM3                TRUE
#define STM32_PWM_USE_TIM3          TRUE
#define STM32_TIM3_SUPPRESS_ISR     FALSE

/* GPT driver system settings - for RGB effects timers */
#define GPT_USE_TIM2                TRUE
#define STM32_GPT_USE_TIM2          TRUE

/* RTC driver system settings */
#define RTC_IRQ_PRIORITY            15

/* Include the default HAL settings */
#include_next <halconf.h>