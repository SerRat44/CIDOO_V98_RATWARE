/*
 * This file is part of the QMK Firmware for Cidoo V98
 *
 * Copyright (c) 2023 QMK Community
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "hal.h"
#include "board.h"

#if HAL_USE_PAL || defined(__DOXYGEN__)
/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
const PALConfig pal_default_config = {
    // GPIO Port A setup
    {VAL_GPIOA_MODER, VAL_GPIOA_OTYPER, VAL_GPIOA_OSPEEDR, VAL_GPIOA_PUPDR,
     VAL_GPIOA_ODR,   VAL_GPIOA_AFRL,   VAL_GPIOA_AFRH},
    
    // GPIO Port B setup
    {VAL_GPIOB_MODER, VAL_GPIOB_OTYPER, VAL_GPIOB_OSPEEDR, VAL_GPIOB_PUPDR,
     VAL_GPIOB_ODR,   VAL_GPIOB_AFRL,   VAL_GPIOB_AFRH},
     
    // GPIO Port C setup
    {VAL_GPIOC_MODER, VAL_GPIOC_OTYPER, VAL_GPIOC_OSPEEDR, VAL_GPIOC_PUPDR,
     VAL_GPIOC_ODR,   VAL_GPIOC_AFRL,   VAL_GPIOC_AFRH},
     
    // GPIO Port D setup
    {VAL_GPIOD_MODER, VAL_GPIOD_OTYPER, VAL_GPIOD_OSPEEDR, VAL_GPIOD_PUPDR,
     VAL_GPIOD_ODR,   VAL_GPIOD_AFRL,   VAL_GPIOD_AFRH}
};
#endif

/**
 * @brief   Early initialization code.
 * @details This initialization must be performed just after stack setup
 *          and before any other initialization.
 */
void __early_init(void) {
    stm32_clock_init();
}

/**
 * @brief   Board-specific initialization code.
 * @note    Implemented to initialize the Bluetooth module and battery
 *          management hardware.
 */
void boardInit(void) {
    // Enable USART3 for Bluetooth communication
    rccEnableUSART3(true);
    
    // Configure battery monitoring ADC
    rccEnableADC1(true);
    
    // Set initial state for Bluetooth module (powered down to save battery)
    palClearPad(GPIOB, GPIOB_BT_POWER);
    palClearPad(GPIOB, GPIOB_BT_RESET);
    
    // Initialize USB disconnect hardware
#if BOARD_USB_DISCONNECTION
    palSetPadMode(GPIOB, GPIOB_USB_DISCONNECT, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(GPIOB, GPIOB_USB_DISCONNECT);
#endif
}

/**
 * @brief   Battery level reading
 * @details Reads the battery voltage through ADC
 * @return  Battery level in percentage (0-100)
 */
uint8_t board_get_battery_level(void) {
    // Configure ADC for battery reading
    ADC1->CR2 |= ADC_CR2_ADON;
    ADC1->SQR3 = GPIOA_BAT_SENSE;
    
    // Start conversion
    ADC1->CR2 |= ADC_CR2_SWSTART;
    
    // Wait for completion
    while (!(ADC1->SR & ADC_SR_EOC));
    
    // Read ADC value
    uint16_t adc_value = ADC1->DR;
    
    // Convert to percentage (scale based on battery characteristics)
    // Assuming 3.7V Li-ion/LiPo battery, ADC reference of 3.3V, and voltage divider
    // Full battery ~4.2V, empty ~3.2V
    // Calculate percentage, constrained between 0-100
    int32_t percentage = ((adc_value * 330 / 4095) - 320) * 100 / 100;
    if (percentage > 100) percentage = 100;
    if (percentage < 0) percentage = 0;
    
    return (uint8_t)percentage;
}

/**
 * @brief   Charging status check
 * @return  True if battery is charging
 */
bool board_is_charging(void) {
    // Check charge detection pin
    return !palReadPad(GPIOA, GPIOA_BAT_CHARGE_DETECT);
}