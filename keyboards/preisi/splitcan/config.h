// Copyright 2022-2024 Thomas Preisner(@preisi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Bootloader
#define STM32_BOOTLOADER_DUAL_BANK TRUE
#define STM32_BOOTLOADER_DUAL_BANK_GPIO A0
#define STM32_BOOTLOADER_DUAL_BANK_DELAY 1600

// Split configuration
#define SPLIT_HAND_PIN B1
#define SPLIT_TRANSACTION_IDS_KB RPC_ID_SYNC_STATE_KB
#define USB_VBUS_PIN B11
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_WPM_ENABLE

// SPI Configuration for EEPROM
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A7
#define SPI_MISO_PIN A6

// TODO: get unique VID + PID

// Current Limiter Configuration
#define RGB_POWER_ENABLE_PIN C6
#define RGB_CURR_1500mA_OK_PIN B15
#define RGB_CURR_3000mA_OK_PIN B14

// RGB configuration
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM1   // TODO: WHICH DMA_STREAM??
#define WS2812_DMA_CHANNEL 1                   // TODO: CHANNEL ??
#define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM3_UP // TODO: DMAMUX??

// TODO: make configurable for ANSI-layout: { 38 , 39 }
// TODO: remove RGBLED_NUM ?
#define RGBLED_NUM 78
#define RGB_MATRIX_LED_COUNT 78
#define RGB_MATRIX_SPLIT \
    { 38, 40 }
#define RGB_DISABLE_WHEN_USB_SUSPEND
#define RGB_DISABLE_TIMEOUT 90000 // disable rgb lighting after 15mins of inactivity

// Matrix
/*
#define MATRIX_ROWS 12
#define MATRIX_COLS 7
#define MATRIX_ROW_PINS \
    { B2, C11, A1, F1, F0, C15 }
#define MATRIX_COL_PINS \
    { A3, A2, C14, C13, B7, C10, A15 }
#define MATRIX_ROW_PINS_RIGHT \
    { A8, B10, A1, A2, A3, C11 }
#define MATRIX_COL_PINS_RIGHT \
    { F1, F0, C15, C14, C13, C10, A15 }
#define DIODE_DIRECTION COL2ROW
*/

// FDCAN Configuration
#define FDCAN_RX_PIN B12
#define FDCAN_TX_PIN B13
// old: #define FDCAN_NBTP (4U << FDCAN_DBTP_DSJW_Pos) | (3U << FDCAN_DBTP_DTSEG2_Pos) | (4U << FDCAN_DBTP_DTSEG1_Pos) | (0U << FDCAN_DBTP_DBRP_Pos)
// old: #define FDCAN_DBTP (15U << FDCAN_NBTP_NTSEG2_Pos) | (62U << FDCAN_NBTP_NTSEG1_Pos) | (0U << FDCAN_NBTP_NBRP_Pos) | (15U << FDCAN_NBTP_NSJW_Pos)
// old: #define FDCAN_CKDIV (2U << FDCAN_CKDIV_PDIV_Pos) // 2.5MBaud -> works with can-frames
// less old: #define FDCAN_CKDIV (1U << FDCAN_CKDIV_PDIV_Pos) // 5MBaud -> requires fdcan-frames

// EEPROM configuration
#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN A4
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 16 // (160MHz / 16) -> 10MHz
#define EXTERNAL_EEPROM_BYTE_COUNT 65536
#define EXTERNAL_EEPROM_PAGE_SIZE 128

/*
// enable all rgb modes
#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_BAND_VAL
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_HUE_PENDULUM
#define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_PIXEL_RAIN
#define ENABLE_RGB_MATRIX_PIXEL_FLOW
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN
// enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
*/
