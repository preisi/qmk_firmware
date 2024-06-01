// Copyright 2022-2024 Thomas Preisner (@preisi)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "splitcan.h"
#include <string.h>
#include <hal.h>
#include "transactions.h"
#include "split_util.h"

kb_runtime_config kb_state;

void board_init(void) {
    usbpd_init();
}

const char* usbpd_str(usbpd_allowance_t allowance) {
    switch (allowance) {
        default:
        case USBPD_500MA:
            return "500mA";
        case USBPD_1500MA:
            return "1500mA";
        case USBPD_3000MA:
            return "3000mA";
    }
}

void usbpd_update(void) {
    static uint32_t last_read = 0;
    if (timer_elapsed32(last_read) > 250) {
        last_read = timer_read32();

        usbpd_allowance_t allowance = usbpd_get_allowance();
        if (kb_state.current_setting != allowance) {
            dprintf("Transitioning UCPD1 %s -> %s\n", usbpd_str(kb_state.current_setting), usbpd_str(allowance));
            kb_state.current_setting = allowance;
        }
    }
}

void kb_state_update(void) {
    if (is_keyboard_master()) {
        // Modify allowed current limits
        usbpd_update();
    }
}

void kb_state_sync(void) {
    if (!is_transport_connected()) {
        return;
    }

    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static kb_runtime_config last_kb_state;
        static uint32_t          last_sync;
        bool                     needs_sync = false;

        // Check if the state values are different
        if (memcmp(&kb_state, &last_kb_state, sizeof(kb_runtime_config))) {
            needs_sync = true;
            memcpy(&last_kb_state, &kb_state, sizeof(kb_runtime_config));
        }

        // Send to slave every 500ms regardless of state change
        if (needs_sync == false && timer_elapsed32(last_sync) > 500) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_SYNC_STATE_KB, sizeof(kb_runtime_config), &kb_state)) {
                last_sync = timer_read32();
            } else {
                dprint("Failed to perform data transaction\n");
            }
        }
    }
}

void kb_state_sync_slave(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(kb_runtime_config)) {
        memcpy(&kb_state, initiator2target_buffer, sizeof(kb_runtime_config));
    }
}

void housekeeping_task_kb(void) {
    // Update kb_state so we can send to slave
    kb_state_update();

    // Data sync from master to slave
    kb_state_sync();

    // Work out if we've changed our current limit, update the limiter circuit switches
    static uint8_t current_setting = USBPD_500MA;
    if (current_setting != kb_state.current_setting) {
        current_setting = kb_state.current_setting;
        switch (current_setting) {
            default:
            case USBPD_500MA:
                gpio_set_pin_input(RGB_CURR_1500mA_OK_PIN);
                gpio_set_pin_input(RGB_CURR_3000mA_OK_PIN);
                break;
            case USBPD_1500MA:
                gpio_set_pin_output_open_drain(RGB_CURR_1500mA_OK_PIN);
                gpio_set_pin_input(RGB_CURR_3000mA_OK_PIN);
                break;
            case USBPD_3000MA:
                gpio_set_pin_output_open_drain(RGB_CURR_1500mA_OK_PIN);
                gpio_set_pin_output_open_drain(RGB_CURR_3000mA_OK_PIN);
                break;
        }
    }
}

void keyboard_post_init_kb(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(RPC_ID_SYNC_STATE_KB, kb_state_sync_slave);

    // Reset the initial shared data value between master and slave
    memset(&kb_state, 0, sizeof(kb_state));

    // Turn off increased current limits by making pins float
    gpio_set_pin_input(RGB_CURR_1500mA_OK_PIN);
    gpio_set_pin_input(RGB_CURR_3000mA_OK_PIN);

    // Turn on the RGB
    gpio_set_pin_output(RGB_POWER_ENABLE_PIN);
    gpio_write_pin_high(RGB_POWER_ENABLE_PIN);

    // Allow for user post-init
    keyboard_post_init_user();
}

//----------------------------------------------------------
// QMK overrides

#if defined(RGB_MATRIX_ENABLE)
#    define rgb_to_hsv_hook_func rgb_matrix_hsv_to_rgb
#elif defined(RGBLIGHT_ENABLE)
#    define rgb_to_hsv_hook_func rgblight_hsv_to_rgb
#endif
RGB rgb_to_hsv_hook_func(HSV hsv) {
    float scale;
    switch (kb_state.current_setting) {
        default:
        case USBPD_500MA:
            scale = 0.35f;
            break;
        case USBPD_1500MA:
            scale = 0.75f;
            break;
        case USBPD_3000MA:
            scale = 1.0f;
            break;
    }

    hsv.v = (uint8_t)(hsv.v * scale);
    return hsv_to_rgb(hsv);
}

/*
#ifdef RGB_MATRIX_ENABLE
// clang-format off
// TODO: 37 for Left ANSI
#define RLO 38
#define LLI(x) (x)
#define RLI(x) (RLO+(x))
#define LP(x,y) {(x),(y)}
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { LLI( 0),  LLI( 1), LLI( 2), LLI( 3), LLI( 4), LLI( 5), LLI( 6) },
        { LLI(13),  LLI(12), LLI(11), LLI(10), LLI( 9), LLI( 8), LLI( 7) },
        {  NO_LED,  LLI(14), LLI(15), LLI(16), LLI(17), LLI(18), LLI(19) },
        {  NO_LED,  LLI(25), LLI(24), LLI(23), LLI(22), LLI(21), LLI(20) },
        { LLI(26),  LLI(27), LLI(28), LLI(29), LLI(30), LLI(31), LLI(32) },
        {  NO_LED,   NO_LED, LLI(37), LLI(36), LLI(35), LLI(34), LLI(33) },
        { RLI( 0),  RLI( 1), RLI( 2), RLI( 3), RLI( 4), RLI( 5), RLI( 6) },
        { RLI(13),  RLI(12), RLI(11), RLI(10), RLI( 9), RLI( 8), RLI( 7) },
        { RLI(14),  RLI(15), RLI(16), RLI(17), RLI(18), RLI(19), RLI(20) },
        { RLI(27),  RLI(26), RLI(25), RLI(24), RLI(23), RLI(22), RLI(21) },
        { RLI(28),  RLI(29), RLI(30), RLI(31), RLI(32), RLI(33), RLI(34) },
        {  NO_LED,  RLI(39),  NO_LED, RLI(38), RLI(37), RLI(36), RLI(35) },
    },
    {
        // 1U -> 12 in y, 16 in x. 0.25U -> 4 in y, 4 in x
        // LED Index to Physical Position
        // Matrix left
        LP(  0,  0), LP( 20,  0), LP( 36,  0), LP( 52,  0), LP( 68,  0), LP( 88,  0), LP(104,  0),
        LP(  0, 16), LP( 16, 16), LP( 32, 16), LP( 48, 16), LP( 64, 16), LP( 80, 16), LP( 96, 16),
        LP(  4, 28), LP( 24, 28), LP( 40, 28), LP( 56, 28), LP( 72, 28), LP( 88, 28),
        LP(  6, 40), LP( 28, 40), LP( 44, 40), LP( 60, 40), LP( 76, 40), LP( 92, 40),
        // ANSI: LP(  6, 40), LP( 28, 40), LP( 44, 40), LP( 60, 40), LP( 76, 40), LP( 92, 40),
        LP(  2, 52), LP( 20, 52), LP( 36, 52), LP( 52, 52), LP( 68, 52), LP( 84, 52), LP(100, 52),
        // ANSI: LP(  2, 52), LP( 20, 52), LP( 36, 52), LP( 52, 52), LP( 68, 52), LP( 84, 52), LP(100, 52),
        LP(  2, 64), LP( 22, 64), LP( 42, 64), LP( 62, 64), LP( 90, 64),
        // Matrix right
        LP(120,  0), LP(136,  0), LP(156,  0), LP(172,  0), LP(188,  0), LP(204,  0), LP(224,  0),
        LP(112, 16), LP(128, 16), LP(144, 16), LP(160, 16), LP(176, 16), LP(192, 16), LP(216, 16),
        LP(104, 28), LP(120, 28), LP(136, 28), LP(152, 28), LP(168, 28), LP(184, 28), LP(200, 28),
        LP(108, 40), LP(124, 40), LP(140, 40), LP(156, 40), LP(172, 40), LP(188, 40), LP(204, 40),
        LP(116, 52), LP(132, 52), LP(148, 52), LP(164, 52), LP(180, 52), LP(210, 52), LP(222, 34),
        // ANSI: LP(108, 40), LP(124, 40), LP(140, 40), LP(156, 40), LP(172, 40), LP(188, 40), LP(220, 28),
        // ANSI: LP(116, 52), LP(132, 52), LP(148, 52), LP(164, 52), LP(180, 52), LP(210, 52), LP(210, 40),
        LP(130, 64),              LP(162, 64), LP(182, 64), LP(202, 64), LP(222, 64),
    },
    {
        // LED Index to Flag
        // Matrix left
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
                           LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
                           LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
                                              LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        // Matrix right
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
                           LED_FLAG_KEYLIGHT,                    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    }
};
// clang-format on
#endif  // RGB_MATRIX_ENABLE
*/
