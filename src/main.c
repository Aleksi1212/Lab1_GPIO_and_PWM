#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"

#define LED_1 20
#define LED_2 21
#define LED_3 22

#define SW_0 7
#define SW_1 8
#define SW_2 9

void init_led_pin(uint gpio)
{
	gpio_init(gpio);
	gpio_set_dir(gpio, GPIO_OUT);
}

void init_button_pin(uint gpio)
{
	gpio_init(gpio);
	gpio_set_dir(gpio, GPIO_IN);
  	gpio_pull_up(gpio);
}

void toggle_leds(int mode)
{
  	gpio_put(LED_1, mode);
  	gpio_put(LED_2, mode);
  	gpio_put(LED_3, mode);
}

int main(void)
{
	init_led_pin(LED_1);
	init_led_pin(LED_2);
	init_led_pin(LED_3);

	init_button_pin(SW_0);
	init_button_pin(SW_1);
	init_button_pin(SW_2);

	stdio_init_all();

	bool pressed = false;
	bool led_mode = true;

	while (true)
	{
		if (pressed && !gpio_get(SW_1)) {
			pressed = false;
		}
		else if (!pressed && gpio_get(SW_1)) {
			led_mode = !led_mode;
			pressed = true;
			sleep_ms(50);
		}

		toggle_leds(led_mode);

		if (led_mode) {
			
		}
	}
	
	return 0;
}