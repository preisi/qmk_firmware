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

#include <quantum.h>

//----------------------------------------------------------
// Runtime data sync -- keyboard

#pragma pack(push)
#pragma pack(1)

typedef struct kb_runtime_config {
    usbpd_allowance_t current_setting : 2;
} kb_runtime_config;

#pragma pack(pop)

_Static_assert(sizeof(kb_runtime_config) == 1, "Invalid data transfer size for keyboard sync data");

extern kb_runtime_config kb_state;

const char *usbpd_str(usbpd_allowance_t allowance);
