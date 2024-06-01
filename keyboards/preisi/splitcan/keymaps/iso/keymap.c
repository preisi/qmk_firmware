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

#include QMK_KEYBOARD_H
#include <string.h>
#include <printf.h>

// Layer definitions
enum { _QWERTY, _LOWER, _RAISE, _ADJUST };

#define KC_LWR MO(_LOWER)
#define KC_RSE MO(_RAISE)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_iso(
         KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL,
         KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,       KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSPC,
                  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,
        KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, KC_BSLS,
        KC_LSFT,    KC_Z,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,  KC_ENT,
		KC_LCTL, KC_LGUI, KC_LALT,  KC_LWR,  KC_SPC,                                KC_SPC,          KC_RALT, KC_RGUI,  KC_RSE, KC_RCTL
    ),
    [_LOWER] = LAYOUT_iso(
        QK_BOOT, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_BRID, KC_BRIU,    _______, _______, KC_PGUP, KC_PGDN, KC_HOME,  KC_END, QK_BOOT,
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,             KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,  KC_INS,
		_______, _______, _______, _______, RGB_MOD,                               RGB_MOD,          _______, _______, _______, _______
    ),
    [_RAISE] = LAYOUT_iso(
        QK_BOOT, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_BRID, KC_BRIU,    _______, _______, KC_PGUP, KC_PGDN, KC_HOME,  KC_END, QK_BOOT,
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,             KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,  KC_INS,
		_______, _______, _______, _______, _______,                               _______,          _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT_iso(
        QK_BOOT, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, QK_BOOT,
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
                 _______, _______, RGB_VAI, RGB_TOG, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RGB_SPD, RGB_VAD, RGB_SPI, _______,             _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______,                               _______,          _______, _______, _______, _______
    )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Default handler for lower/raise/adjust
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
