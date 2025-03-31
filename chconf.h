/*
 * This file is part of the QMK Firmware for Cidoo V98
 *
 * Copyright (c) 2023 QMK Community
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

/**
 * @file    chconf.h
 * @brief   ChibiOS configuration for QMK
 */

#pragma once

#define CH_CFG_ST_FREQUENCY                 10000

#define CH_CFG_OPTIMIZE_SPEED               TRUE

#define CH_CFG_USE_CONDVARS                 TRUE
#define CH_CFG_USE_CONDVARS_TIMEOUT         TRUE
#define CH_CFG_USE_EVENTS                   TRUE
#define CH_CFG_USE_EVENTS_TIMEOUT           TRUE
#define CH_CFG_USE_MESSAGES                 TRUE
#define CH_CFG_USE_MESSAGES_PRIORITY        FALSE
#define CH_CFG_USE_MAILBOXES                TRUE
#define CH_CFG_USE_MEMCORE                  TRUE
#define CH_CFG_USE_HEAP                     TRUE
#define CH_CFG_USE_MEMPOOLS                 TRUE
#define CH_CFG_USE_OBJ_FIFOS                TRUE
#define CH_CFG_USE_DYNAMIC                  TRUE
#define CH_CFG_USE_FACTORY                  TRUE
#define CH_CFG_FACTORY_MAX_NAMES_LENGTH     8
#define CH_CFG_FACTORY_OBJECTS_REGISTRY     TRUE
#define CH_CFG_FACTORY_GENERIC_BUFFERS      TRUE
#define CH_CFG_FACTORY_SEMAPHORES           TRUE
#define CH_CFG_FACTORY_MAILBOXES            TRUE
#define CH_CFG_FACTORY_OBJ_FIFOS            TRUE

/*
 * Optimized for low power consumption
 * This is important for a battery-powered keyboard
 */
#define CH_CFG_ST_TIMEDELTA                 2

/* Feature-specific configurations for Bluetooth and encoder. */
/* USB and Bluetooth switching threads need high priority */
#define CH_CFG_OPTIMIZE_SPEED               TRUE
#define CH_CFG_USE_MUTEXES                  TRUE
#define CH_CFG_USE_MUTEXES_RECURSIVE        FALSE
#define CH_CFG_USE_SEMAPHORES               TRUE

/* Set thread priorities for specialized functions */
#define PORT_INT_REQUIRED_STACK             16

/* Threads for matrix scanning and wireless module */
#define CORTEX_PRIORITY_PENDSV              (CORTEX_MAXIMUM_PRIORITY - 0)
#define CORTEX_PRIORITY_SYSTICK             (CORTEX_MAXIMUM_PRIORITY - 1)
#define CORTEX_PRIORITY_USB                 (CORTEX_MAXIMUM_PRIORITY - 2)
#define CORTEX_PRIORITY_MATRIX_SCAN         (CORTEX_MAXIMUM_PRIORITY - 3)
#define CORTEX_PRIORITY_BLUETOOTH           (CORTEX_MAXIMUM_PRIORITY - 4)
#define CORTEX_PRIORITY_ENCODER             (CORTEX_MAXIMUM_PRIORITY - 5)

/* Memory for keymap storage and bluetooth buffers */
#define CH_CFG_MEMCORE_SIZE                 (1 * 1024)
#define CH_CFG_HEAP_CAPACITY                (3 * 1024)

/* Duration between system ticks (in microseconds) */
#define CH_CFG_ST_RESOLUTION                32
#define CH_CFG_INTERVALS_SIZE               32
#define CH_CFG_TIME_TYPES_SIZE              32

/* Reduce idle thread stack to save memory */
#define CH_CFG_IDLE_THREAD_STACK_SIZE       32

/* Sleep Modes for power management */
#define CH_CFG_USE_WAITEXIT                 TRUE
#define CH_CFG_USE_SLEEP                    TRUE

/* Include default ChibiOS configurations */
#include_next <chconf.h>