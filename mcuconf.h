/*
 * This file is part of the QMK Firmware for Cidoo V98
 *
 * Copyright (c) 2023 QMK Community
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

/**
 * @file    mcuconf.h
 * @brief   STM32F103 MCU specific configuration.
 */

#pragma once

/* STM32F103 system settings - optimized for keyboard use */
#define STM32_NO_INIT                       FALSE
#define STM32_HSI_ENABLED                   TRUE
#define STM32_LSI_ENABLED                   TRUE
#define STM32_HSE_ENABLED                   TRUE
#define STM32_LSE_ENABLED                   FALSE
#define STM32_SW                            STM32_SW_PLL
#define STM32_PLLSRC                        STM32_PLLSRC_HSE
#define STM32_PLLXTPRE                      STM32_PLLXTPRE_DIV1
#define STM32_PLLMUL_VALUE                  9
#define STM32_HPRE                          STM32_HPRE_DIV1
#define STM32_PPRE1                         STM32_PPRE1_DIV2
#define STM32_PPRE2                         STM32_PPRE2_DIV2
#define STM32_ADCPRE                        STM32_ADCPRE_DIV4
#define STM32_USB_CLOCK_REQUIRED            TRUE
#define STM32_USBPRE                        STM32_USBPRE_DIV1P5
#define STM32_MCOSEL                        STM32_MCOSEL_NOCLOCK
#define STM32_RTCSEL                        STM32_RTCSEL_HSEDIV
#define STM32_PVD_ENABLE                    FALSE
#define STM32_PLS                           STM32_PLS_LEV0

/* Optimized for power efficiency */
#define STM32_ADC_USE_ADC1                  TRUE   /* For battery monitoring */
#define STM32_CAN_USE_CAN1                  FALSE
#define STM32_DAC_USE_DAC1_CH1              FALSE
#define STM32_DAC_USE_DAC1_CH2              FALSE
#define STM32_DMA_SUPPORTS_DMAMUX           FALSE
#define STM32_PWM_USE_ADVANCED              FALSE
#define STM32_QEI_USE_TIM1                  FALSE
#define STM32_QEI_USE_TIM2                  FALSE
#define STM32_QEI_USE_TIM3                  FALSE
#define STM32_QEI_USE_TIM4                  FALSE
#define STM32_QEI_USE_TIM5                  FALSE
#define STM32_QEI_USE_TIM8                  FALSE
#define STM32_RTC_PRESA_VALUE               32
#define STM32_RTC_PRESS_VALUE               1024
#define STM32_SDC_USE_SDMMC1                FALSE
#define STM32_SPI_USE_SPI1                  FALSE
#define STM32_SPI_USE_SPI2                  FALSE
#define STM32_SPI_USE_SPI3                  FALSE
#define STM32_UART_USE_USART1               FALSE
#define STM32_UART_USE_USART2               FALSE

/* UART3 for Bluetooth communication */
#define STM32_SERIAL_USE_USART1             FALSE
#define STM32_SERIAL_USE_USART2             FALSE
#define STM32_SERIAL_USE_USART3             TRUE
#define STM32_SERIAL_USART3_PRIORITY        11

/* USB driver system settings */
#define STM32_USB_USE_USB1                  TRUE
#define STM32_USB_LOW_POWER_ON_SUSPEND      TRUE
#define STM32_USB_USB1_HP_IRQ_PRIORITY      13
#define STM32_USB_USB1_LP_IRQ_PRIORITY      14

/* I2C driver system settings */
#define STM32_I2C_I2C1_RX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 7)
#define STM32_I2C_I2C1_TX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 6)
#define STM32_I2C_I2C1_IRQ_PRIORITY         5
#define STM32_I2C_I2C1_DMA_PRIORITY         3
#define STM32_I2C_DMA_ERROR_HOOK(i2cp)      osalSysHalt("DMA failure")

/* DMA driver settings */
#define STM32_DMA_REQUIRED                  TRUE
#define STM32_DMA_SUPPORTS_CSELR            FALSE
#define STM32_DMA1_NUM_CHANNELS             7
#define STM32_DMA2_NUM_CHANNELS             0

/* PWM for LED control */
#define STM32_GPT_USE_TIM1                  FALSE
#define STM32_GPT_USE_TIM2                  TRUE
#define STM32_GPT_USE_TIM3                  FALSE
#define STM32_GPT_USE_TIM4                  FALSE
#define STM32_GPT_TIM2_IRQ_PRIORITY         7

/* Timer config for encoder */
#define STM32_TIM_UP_INTERRUPTS             TRUE
#define STM32_TIM_IRQ_PRIORITY              6

/* Include the default MCU settings */
#include_next <mcuconf.h>