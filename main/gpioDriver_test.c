#include "gpioDriver_test.h"

static const char *TAG = "GPIO Driver Test";

void gpio_driver_out_task(void *pvParameter)
{
    uint8_t i;
    uint8_t GPIO_level;
    GPIO_DriverRetVal_e GPIO_Driver_init_success;
    GPIO_DriverGPIOConfig_s GPIO_pin_def_LED1;
    GPIO_DriverGPIOConfig_s GPIO_pin_def_BUTTON1;

    ESP_LOGI(TAG, "GPIO Driver Init Start");
    GPIO_pin_def_LED1.GPIO_Pin_Port = 0;
    GPIO_pin_def_LED1.GPIO_Pin_Number = LED1_GPIO;
    GPIO_pin_def_LED1.GPIO_PullUpDown_Selector = GPIO_DriverGPIO_FLOATING;
    GPIO_Driver_init_success = gpioDriverPinInit_Output(&GPIO_pin_def_LED1);
    GPIO_pin_def_BUTTON1.GPIO_Pin_Port = 0;
    GPIO_pin_def_BUTTON1.GPIO_Pin_Number = BUTTON1_GPIO;
    GPIO_pin_def_BUTTON1.GPIO_PullUpDown_Selector = GPIO_DriverGPIO_FLOATING;
    GPIO_Driver_init_success = gpioDriverPinInit_Input(&GPIO_pin_def_BUTTON1);
    ESP_LOGI(TAG, "GPIO Driver Init Done");
    ESP_LOGI(TAG, "Set GPIO Pin Level to High");
    gpioDriverSetPin_Level(&GPIO_pin_def_LED1, GPIO_DriverGPIOLevel_High);
    gpioDriverReadPin(&GPIO_pin_def_LED1, &GPIO_level);
    ESP_LOGI(TAG, "GPIO read level: %d", GPIO_level);
    vTaskDelay(PIN_TOGGLE_DELAY_MS / portTICK_RATE_MS);
    for (i = 0; i < 10; i++)
    {
        ESP_LOGI(TAG, "Toggle GPIO Pin Level");
        gpioDriverTogglePin(&GPIO_pin_def_LED1);
        gpioDriverReadPin(&GPIO_pin_def_LED1, &GPIO_level);
        ESP_LOGI(TAG, "GPIO LED1 read level: %d", GPIO_level);
        gpioDriverReadPin(&GPIO_pin_def_BUTTON1, &GPIO_level);
        ESP_LOGI(TAG, "GPIO BUTTON1 read level: %d", GPIO_level);
        vTaskDelay(PIN_TOGGLE_DELAY_MS / portTICK_RATE_MS);
    }
    ESP_LOGI(TAG, "Set GPIO Pin Level to Low");
    gpioDriverSetPin_Level(&GPIO_pin_def_LED1, GPIO_DriverGPIOLevel_Low);
    gpioDriverReadPin(&GPIO_pin_def_LED1, &GPIO_level);
    ESP_LOGI(TAG, "GPIO read level: %d", GPIO_level);
    vTaskDelay(PIN_TOGGLE_DELAY_MS / portTICK_RATE_MS);
    ESP_LOGI(TAG, "GPIO Driver DeInit");
    gpioDriverPinDeInit(&GPIO_pin_def_LED1);
    ESP_LOGI(TAG, "GPIO Driver Task Stop");
    vTaskDelete(NULL);
}
