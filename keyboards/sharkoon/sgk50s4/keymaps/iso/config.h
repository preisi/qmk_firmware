/*
Copyright 2022 Thomas Preisner <mail@tpreisner.de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"
#include "config_led.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x0C45
#define PRODUCT_ID 0x8006
#define DEVICE_VER 0x0001

#define MANUFACTURER Sharkoon Technologies GmbH
#define PRODUCT SKILLER SGK50 S4

/* Additional options */
#define RGB_MATRIX_ENABLE 1
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#define RGB_MATRIX_STARTUP_SPD 32

/* Key matrix */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14
#define DIODE_DIRECTION ROW2COL
#define MATRIX_COL_PINS \
    { A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, D0, D1, D2 }
#define MATRIX_ROW_PINS \
    { B1, B2, B3, B4, B5 }

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* RGB matrix -> activate pwm channel for each col pin */
#define ACTIVATE_PWM_CHAN_5
#define ACTIVATE_PWM_CHAN_6
#define ACTIVATE_PWM_CHAN_7
#define ACTIVATE_PWM_CHAN_8
#define ACTIVATE_PWM_CHAN_9
#define ACTIVATE_PWM_CHAN_10
#define ACTIVATE_PWM_CHAN_11
#define ACTIVATE_PWM_CHAN_12
#define ACTIVATE_PWM_CHAN_13
#define ACTIVATE_PWM_CHAN_14
#define ACTIVATE_PWM_CHAN_15
#define ACTIVATE_PWM_CHAN_16
#define ACTIVATE_PWM_CHAN_17
#define ACTIVATE_PWM_CHAN_18
