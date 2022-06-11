/* Copyright 2022 Thomas Preisner (@preisi)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include_next <mcuconf.h>

// Used for SK6812
#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE

// Used for EEPROM
#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE

// Required for configuring (global) FDCAN clock divider
#undef STM32_CAN_USE_FDCAN1
#define STM32_CAN_USE_FDCAN1 TRUE
// Used for custom split communication
#undef STM32_CAN_USE_FDCAN2
#define STM32_CAN_USE_FDCAN2 TRUE

// Use plclk1 as fdcan clock source
#undef STM32_FDCANSEL
#define STM32_FDCANSEL STM32_FDCANSEL_PCLK1
