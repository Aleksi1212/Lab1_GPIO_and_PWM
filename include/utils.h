#include "pico/stdlib.h"

#ifndef UTILS_H
#define UTILS_H

void init_led_pin(uint gpio, uint *slice_num);
void init_button_pin(uint gpio);
void adjust_leds(uint *led_slices, uint16_t level);

#endif
