/**
 * Brief:
 * This test code shows how to 
 *
 *
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"

#include "gpioDriver_test.h"

static const char *TAG = "Driver Test";



void app_main(void)
{
    vTaskDelay(100 / portTICK_RATE_MS);
    xTaskCreate(&gpio_driver_out_task, "gpio_driver_out_task", 2048, NULL, 5, NULL);
}

