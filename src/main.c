#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "../include/constants.h"
#include "../include/utils.h"

int main(void)
{
	uint led_slices[LED_COUNT];

	init_led_pin(LED_1, &led_slices[0]);
	init_led_pin(LED_2, &led_slices[1]);
	init_led_pin(LED_3, &led_slices[2]);

	init_button_pin(SW_0);
	init_button_pin(SW_1);
	init_button_pin(SW_2);

	stdio_init_all();

	bool pressed = false;
	bool led_on = true;

	uint16_t led_level = MAX_LED_LEVEL;

	while (true)
	{
		if (pressed && gpio_get(SW_1) == 0) {
			pressed = false;
		}
		else if (!pressed && gpio_get(SW_1) > 0) {
			if (led_on && led_level == 0)
				led_level = MAX_LED_LEVEL / 2;
			else
				led_on = !led_on;

			pressed = true;
			sleep_ms(10);
		}

		if (led_on) {
			if (gpio_get(SW_0) == 0 && led_level < MAX_LED_LEVEL) {
				led_level += 10;
				sleep_ms(10);
			}
			else if (gpio_get(SW_2) == 0 && led_level > 0) {
				led_level -= 10;
				sleep_ms(10);
			}

			adjust_leds(led_slices, led_level);
		} else {
			adjust_leds(led_slices, 0);
		}
	}
	
	return 0;
}