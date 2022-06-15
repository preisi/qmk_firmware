#pragma once

#include <stdint.h>
#include <stdbool.h>

void SN32F26x_init(void);
#if defined(RGB_MATRIX_ENABLE)
void SN32F26x_set_color(int index, uint8_t r, uint8_t g, uint8_t b);
void SN32F26x_set_color_all(uint8_t r, uint8_t g, uint8_t b);
#elif defined(LED_MATRIX_ENABLE)
void SN32F26x_set_value(int index, uint8_t value);
void SN32F26x_set_value_all(uint8_t value);
#endif
void matrix_scan_keys(matrix_row_t raw_matrix[], uint8_t current);
