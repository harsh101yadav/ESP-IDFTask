#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED1_GPIO 13
#define LED2_GPIO 14

void gpio_init() {
    esp_rom_gpio_pad_select_gpio(LED1_GPIO);
    gpio_set_direction(LED1_GPIO, GPIO_MODE_OUTPUT);

    esp_rom_gpio_pad_select_gpio(LED2_GPIO);
    gpio_set_direction(LED2_GPIO, GPIO_MODE_OUTPUT);
}

void blink_led1(void *pvParameter) {
    while (1) {
        gpio_set_level(LED1_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
        gpio_set_level(LED1_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void blink_led2(void *pvParameter) {
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        gpio_set_level(LED2_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
        gpio_set_level(LED2_GPIO, 0);
    }
}

void app_main() {

    gpio_init();
    xTaskCreate(&blink_led1, "blink_led1", 1024*2, NULL, 5, NULL);
    xTaskCreate(&blink_led2, "blink_led2", 1024*2, NULL, 5, NULL);
}
