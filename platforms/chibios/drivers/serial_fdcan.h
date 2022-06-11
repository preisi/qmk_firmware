// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#include <hal.h>

typedef CANDriver QMKSerialDriver;
typedef CANConfig QMKSerialConfig;

#if !defined(FDCAN_RX_PIN)
#    error FDCAN_RX_PIN not set
#endif
#if !defined(FDCAN_RX_PAL_MODE)
#    define FDCAN_RX_PAL_MODE 9
#endif

#if !defined(FDCAN_TX_PIN)
#    error FDCAN_TX_PIN not set
#endif
#if !defined(FDCAN_TX_PAL_MODE)
#    define FDCAN_TX_PAL_MODE 9
#endif

#if !defined(FDCAN_NBTP)
#    define FDCAN_NBTP 0x06000A03 // use default value from stm32g4 reference manual
#endif

#if !defined(FDCAN_DBTP)
#    define FDCAN_DBTP 0x00000A33 // use default value from stm32g4 reference manual
#endif

#if !defined(FDCAN_CKDIV)
#    define FDCAN_CKDIV 0
#endif
