// Copyright 2022 QMK
// Copyright 2022 Thomas Preisner
// SPDX-License-Identifier: GPL-2.0-or-later

#include "serial_fdcan.h"
#include "serial_protocol.h"
#include "synchronization_util.h"

#include <debug.h>
#include <assert.h>

// TODO: decide on a proper way to define which fdcan-instance to use for
//       actual communication (FDCAN1 needs to be set for changing CKDIV_PDIV)
static CANDriver *can_config = &CAND1;
#if STM32_CAN_USE_FDCAN2
static CANDriver *serial_driver = &CAND2;
#elif STM32_CAN_USE_FDCAN3
static CANDriver *serial_driver = &CAND3;
#else
static CANDriver *serial_driver = &CAND1;
#endif

// TODO: use 64 bytes -> implement handling for DLC > 8
#define FDCAN_MAX_MSGSIZE 8
#define min(a, b) a < b ? a : b;

#define SERIAL_FDCAN_TIMEOUT 20

static QMKSerialConfig serial_config = {
    .NBTP = FDCAN_NBTP,
    .DBTP = 0,
    // TODO: maybe reenable automatic retransmission
    .CCCR = FDCAN_CCCR_DAR | FDCAN_CCCR_FDOE | FDCAN_CCCR_BRSE,
    .TEST = 0,
    // TODO: set this field in a smart way (contains number of filters, etc)
    .RXGFC = 0,
    .CKDIV = FDCAN_CKDIV,
};

static inline void fdcan_init(void) {
    static bool is_initialized = false;
    if (!is_initialized) {
        is_initialized = true;

        dprintf("Initializing FDCAN pins\n");
        palSetPadMode(PAL_PORT(FDCAN_TX_PIN),
                      PAL_PAD(FDCAN_TX_PIN),
                      PAL_MODE_ALTERNATE(FDCAN_TX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
        palSetPadMode(PAL_PORT(FDCAN_RX_PIN),
                      PAL_PAD(FDCAN_RX_PIN),
                      PAL_MODE_ALTERNATE(FDCAN_RX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);

        // configure ckdiv via fdcan1
        canStart(can_config, &serial_config);
        canStop(can_config);

        dprintf("Starting FDCAN interface..\n");
        canStart(serial_driver, &serial_config);
    }
}

/**
 * @brief Clear the receive input queue.
 */
inline void serial_transport_driver_clear(void) {
    canStop(serial_driver);
    canStart(serial_driver, &serial_config);
}

/**
 * @brief Slave specific initializations.
 */
void serial_transport_driver_slave_init(void) {
    fdcan_init();
}

/**
 * @brief Master specific initializations.
 */
void serial_transport_driver_master_init(void) {
    fdcan_init();
}

/**
 * @brief  Receive of size * bytes.
 *
 * @return true Receive success.
 * @return false Receive failed.
 */
static inline bool fdcan_receive(uint8_t* destination, const size_t size, sysinterval_t timeout) {
    // read length and then receive and merge transaction data packages
    CANRxFrame crf = {0};
    for (uint16_t p = 0; p * FDCAN_MAX_MSGSIZE < size; ++p) {
        msg_t res = canReceiveTimeout(serial_driver, CAN_ANY_MAILBOX, &crf, timeout);
        if (res == MSG_RESET) {
            dprintf("reset during receive, failed...\n");
            return false;
        } else if (res == MSG_TIMEOUT) {
            dprintf("timeout during receive, failed...\n");
            return false;
        } else if (res != MSG_OK) {
            dprintf("unknown fail during receive...\n");
            return false;
        }

        uint16_t plen = min(FDCAN_MAX_MSGSIZE, size - p * FDCAN_MAX_MSGSIZE);
        if (plen != crf.DLC) {
            // most likely message order got screwed up somehow..
            dprintf("receive: assert failed: plen=\n");
        }
        assert(plen == crf.DLC);
        for (uint16_t i = 0; i < plen; ++i) {
            destination[i + p * FDCAN_MAX_MSGSIZE] = crf.data8[i];
        }
    }
    return true;
}

/**
 * @brief  Non-blocking receive of size * bytes.
 *
 * @return true Receive success.
 * @return false Receive failed.
 */
inline bool serial_transport_receive(uint8_t* destination, const size_t size) {
    return fdcan_receive(destination, size, TIME_MS2I(SERIAL_FDCAN_TIMEOUT));
}

/**
 * @brief  Blocking receive of size * bytes with timeout.
 *
 * @return true Receive success.
 * @return false Receive failed, e.g. by timeout.
 */
inline bool serial_transport_receive_blocking(uint8_t* destination, const size_t size) {
    return fdcan_receive(destination, size, TIME_INFINITE);
}

/**
 * @brief Blocking send of buffer with timeout.
 *
 * @return true Send success.
 * @return false Send failed.
 */
inline bool serial_transport_send(const uint8_t* source, const size_t size) {
    // append length and split up transaction data into smaller packages
    CANTxFrame ctf = {0};
    if (is_keyboard_master()) {
        ctf.std.SID = 1;
    } else {
        ctf.std.SID = 2;
    }
    ctf.common.XTD = 0;
    ctf.FDF = 1;

    for (uint16_t p = 0; p * FDCAN_MAX_MSGSIZE < size; ++p) {
        uint16_t sent = p * FDCAN_MAX_MSGSIZE;
        ctf.DLC = min(FDCAN_MAX_MSGSIZE, size - sent);
        for (uint16_t i = 0; i < ctf.DLC; ++i) {
            ctf.data8[i] = source[i + sent];
        }

        msg_t res = canTransmitTimeout(serial_driver, CAN_ANY_MAILBOX, &ctf, TIME_MS2I(SERIAL_FDCAN_TIMEOUT));
        if (res == MSG_RESET) {
            dprintf("reset during send, failed...\n");
            return false;
        } else if (res == MSG_TIMEOUT) {
            dprintf("timeout during send, failed...\n");
            return false;
        } else if (res != MSG_OK) {
            dprintf("unknown fail during send...\n");
            return false;
        }
    }
    return true;
}
