// Copyright 2022-2024 Thomas Preisner (@preisi)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include_next <mcuconf.h>

// Used for SK6812 chain
#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE

// Used for custom split communication
#undef STM32_CAN_USE_FDCAN2
#define STM32_CAN_USE_FDCAN2 TRUE
// Required for configuring (global) FDCAN clock divider
#undef STM32_CAN_USE_FDCAN1
#define STM32_CAN_USE_FDCAN1 TRUE

#define STM32_CAN_CKDIV (1U << FDCAN_CKDIV_PDIV_Pos) // 5MBaud -> requires fdcan-frames

// Use plclk1 as fdcan clock source
#undef STM32_FDCANSEL

// Used for EEPROM
#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE
#define STM32_FDCANSEL STM32_FDCANSEL_PCLK1
