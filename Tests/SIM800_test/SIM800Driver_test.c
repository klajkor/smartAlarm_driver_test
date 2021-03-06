#include "SIM800Driver_test.h"

#define PIN_MODEM_PWKEY 4
#define PIN_MODEM_RST 5
#define PIN_MODEM_POWER_ON 23
#define PIN_MODEM_TX 27
#define PIN_MODEM_RX 26

static const char tag[] = "SIM800Driver_Test";

static const int TEST_UART_BUF_SIZE = 1024;

SIM800Driver_SIM800Config_s Test_SIM800_Config = {
    .Pin_PWKEY = {.GPIO_Pin_Number = PIN_MODEM_PWKEY,
                  .GPIO_Pin_Port = 0,
                  .GPIO_Mode = GPIO_DriverGPIO_MODE_OUTPUT,
                  .GPIO_PullUpDown_Selector = GPIO_DriverGPIO_FLOATING},
    .Pin_RST = {.GPIO_Pin_Number = PIN_MODEM_RST,
                .GPIO_Pin_Port = 0,
                .GPIO_Mode = GPIO_DriverGPIO_MODE_OUTPUT,
                .GPIO_PullUpDown_Selector = GPIO_DriverGPIO_FLOATING},
    .Pin_POWERON = {.GPIO_Pin_Number = PIN_MODEM_POWER_ON,
                    .GPIO_Pin_Port = 0,
                    .GPIO_Mode = GPIO_DriverGPIO_MODE_OUTPUT,
                    .GPIO_PullUpDown_Selector = GPIO_DriverGPIO_FLOATING},
    .SIM800_UART = {.UART_number = UART_NUM_1,
                    .UART_baud_rate = 115200,
                    .UART_data_bits = 8,
                    .UART_stop_bits = 1,
                    .UART_parity = UART_DriverParity_Disable,
                    .UART_TxBuff_Size = TEST_UART_BUF_SIZE,
                    .UART_RxBuff_Size = TEST_UART_BUF_SIZE,
                    .UART_TxGPIO_Pin = PIN_MODEM_TX,
                    .UART_RxGPIO_Pin = PIN_MODEM_RX}};

SIM800Driver_RetVal_e sim800_driver_test(void)
{
    char modem_info[SIM800_MODEM_INFO_MAX_LEN + 1];

    SIM800Driver_RetVal_e testRetVal;
    testRetVal = SIM800Driver_RetVal_OK;
    if (SIM800Driver_SIM800_Init(&Test_SIM800_Config) == SIM800Driver_RetVal_OK)
    {
        ESP_LOGI(tag, "SIM800 Init successful");
    }
    else
    {
        ESP_LOGE(tag, "SIM800 Init failed");
        testRetVal = SIM800Driver_RetVal_NOK;
    }
    if (testRetVal == SIM800Driver_RetVal_OK)
    {
        ESP_LOGI(tag, "Querying SIM800 modem info");
        if (SIM800Driver_SIM800_GetModemInfo(&Test_SIM800_Config, modem_info) == SIM800Driver_RetVal_OK)
        {
            ESP_LOGI(tag, "SIM800 modem info: %s", modem_info);
        }
        else
        {
            ESP_LOGE(tag, "SIM800 modem info invalid: %s", modem_info);
            testRetVal = SIM800Driver_RetVal_NOK;
        }
    }
    return testRetVal;
}
