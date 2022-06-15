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

#ifdef RGB_MATRIX_ENABLE

#    include "rgb_matrix.h"
#    include "config_led.h"

// Force g_led_config into flash, because there is no space in RAM.
// This should be safe because g_led_config should never be written to.
// We cannot make g_led_config const though becuase rgb_matrix.h exports it as
// mutable.
__attribute__(( section(".rodata.g_led_config") ))
led_config_t g_led_config = { {
    {  0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13 },
	{ 14,     15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26, NO_LED },
	{ 27,     28,     29,     30,     31,     32,     33,     34,     35,     36,     37,     38,     39,     40 },
	{ 41,     42,     43,     44,     45,     46,     47,     48,     49,     50,     51,     52,     53, NO_LED },
	{ 54,     55,     56,     57,     58,     59,     60,     61, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
}, {
    {  0,  0}, { 16,  0}, { 32,  0}, { 48,  0}, { 64,  0}, { 80,  0}, { 96,  0}, {112,  0}, {128,  0}, {144,  0}, {160,  0}, {176,  0}, {192,  0}, {216,  0},
	{  4, 16}, { 24, 16}, { 40, 16}, { 56, 16}, { 72, 16}, { 88, 16}, {104, 16}, {120, 16}, {136, 16}, {152, 16}, {168, 16}, {184, 16}, {200, 16},
	{  6, 32}, { 28, 32}, { 44, 32}, { 60, 32}, { 76, 32}, { 92, 32}, {108, 32}, {124, 32}, {140, 32}, {156, 32}, {172, 32}, {196, 32}, {212, 32}, {222, 24},
	{  2, 48}, { 20, 48}, { 36, 48}, { 52, 48}, { 68, 48}, { 84, 48}, {100, 48}, {116, 48}, {132, 48}, {148, 48}, {164, 48}, {180, 48}, {196, 48},
	{  2, 64}, { 22, 64}, { 42, 64}, {102, 64}, {162, 64}, {182, 64}, {202, 64}, { 222, 64},
}, {
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4,           4,         4, 4, 4, 4,
} };

#endif
