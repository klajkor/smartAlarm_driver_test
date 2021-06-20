/**
 * Brief:
 * This test code shows how to 
 *
 *
 */

#define LED1_GPIO 26
#define LED2_GPIO 25
#define PIN_TOGGLE_DELAY_MS 1000

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"

#include "gpioDriver.h"

static const char *TAG = "Driver Test";

void gpio_driver_out_task(void *pvParameter);

void app_main(void)
{
    vTaskDelay( 100 / portTICK_RATE_MS );
	xTaskCreate( &gpio_driver_out_task, "gpio_driver_out_task", 2048, NULL, 5, NULL );    
}

void gpio_driver_out_task(void *pvParameter)
{
    uint8_t i;
    GPIO_DriverRetVal_e GPIO_Driver_init_success;
    GPIO_DriverGPIOInit_s GPIO_pin_def_LED1;

    ESP_LOGI(TAG, "GPIO Driver Init Start");
    GPIO_pin_def_LED1.GPIO_Pin_Port = 0;
    GPIO_pin_def_LED1.GPIO_Pin_Number = LED1_GPIO;
    GPIO_pin_def_LED1.GPIO_PullUpDown_Selector = GPIO_DriverGPIO_FLOATING;
    GPIO_Driver_init_success = gpioDriverPinInit_Output(&GPIO_pin_def_LED1);
    ESP_LOGI(TAG, "GPIO Driver Init Done");
    ESP_LOGI(TAG, "Set GPIO Pin Level to High");
    gpioDriverSetPin_Level(&GPIO_pin_def_LED1, GPIO_DriverGPIOLevel_High);
    vTaskDelay(PIN_TOGGLE_DELAY_MS / portTICK_RATE_MS);
    for(i=0;i<10;i++)
    {
        ESP_LOGI(TAG, "Toggle GPIO Pin Level");
        gpioDriverTogglePin(&GPIO_pin_def_LED1);
        vTaskDelay(PIN_TOGGLE_DELAY_MS / portTICK_RATE_MS);        
    }
    ESP_LOGI(TAG, "Set GPIO Pin Level to Low");
    gpioDriverSetPin_Level(&GPIO_pin_def_LED1, GPIO_DriverGPIOLevel_Low);
    vTaskDelay(PIN_TOGGLE_DELAY_MS / portTICK_RATE_MS);
    ESP_LOGI(TAG, "GPIO Driver DeInit");
    gpioDriverPinDeInit(&GPIO_pin_def_LED1);
    ESP_LOGI(TAG, "GPIO Driver Task Stop");
    vTaskDelete(NULL);
}
