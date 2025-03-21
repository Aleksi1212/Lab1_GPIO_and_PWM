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
  // int state = 1;

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
    // if (led_on) {
    //   printf("Led on\n");
    // } else {
    //   printf("Led off\n");
    // }
    // printf("%d\n", led_on);
    // if (!led_on && !gpio_get(SW_1)) {
    //   led_on = true;
    //   printf("Led on\n");
    // }

    // else if (led_on && !gpio_get(SW_1)) {
    //   led_on = false;
    //   printf("Led off\n");
    // }
  }
  
  return 0;

  // gpio_init(LED_PIN)
  // gpio_init(SW_1)




}

// int main() {

//   // const uint led_pin = 20;
//   // uint count = 0;

//   // // Initialize LED pin
//   // gpio_init(led_pin);
//   // gpio_set_dir(led_pin, GPIO_OUT);

//   // // Initialize chosen serial port
//   // stdio_init_all();

//   // // Loop forever
//   // while (true) {

//   //   // Blink LED
//   //   gpio_put(led_pin, true);
//   //   printf("Blinking! %u\r\n", ++count);
//   //   sleep_ms(1000);
//   //   gpio_put(led_pin, false);
//   //   sleep_ms(1000);
//   // }
// }