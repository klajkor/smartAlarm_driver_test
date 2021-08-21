#include "SIM800Driver_test.h"

#define PIN_MODEM_PWKEY 4
#define PIN_MODEM_RST 5
#define PIN_MODEM_POWER_ON 23
#define PIN_MODEM_TX 27
#define PIN_MODEM_RX 26

static const char tag[] = "SIM800Driver Test";

static const int RX_BUF_SIZE = 511;
static const int TEST_UART_NUM = UART_NUM_2;

SIM800_DriverSIM800Config_s Test_SIM800_Config = {
    .Pin_PWKEY.GPIO_Pin_Number = PIN_MODEM_PWKEY,
    .Pin_PWKEY.GPIO_Pin_Port = 0,
    .Pin_PWKEY.GPIO_Mode = GPIO_DriverGPIO_MODE_OUTPUT,
    .Pin_PWKEY.GPIO_PullUpDown_Selector = GPIO_DriverGPIO_FLOATING,
    .Pin_RST = {
        .GPIO_Pin_Number = PIN_MODEM_RST,
        .GPIO_Pin_Port = 0,
        .GPIO_Mode = GPIO_DriverGPIO_MODE_OUTPUT,
        .GPIO_PullUpDown_Selector = GPIO_DriverGPIO_FLOATING},
    .Pin_POWERON = {.GPIO_Pin_Number = PIN_MODEM_POWER_ON, .GPIO_Pin_Port = 0, .GPIO_Mode = GPIO_DriverGPIO_MODE_OUTPUT, .GPIO_PullUpDown_Selector = GPIO_DriverGPIO_FLOATING}};

UART_DriverUARTConfig_s UART2_config = {.UART_number = TEST_UART_NUM,
                                        .UART_baud_rate = 115200,
                                        .UART_data_bits = 8,
                                        .UART_stop_bits = 1,
                                        .UART_parity = UART_DriverParity_Disable,
                                        .UART_TxBuff_Size = STD_UART_BUF_SIZE,
                                        .UART_RxBuff_Size = STD_UART_BUF_SIZE,
                                        .UART_TxGPIO_Pin = GPIO_NUM_27,
                                        .UART_RxGPIO_Pin = GPIO_NUM_26};

void sim800_driver_test(void)
{
    if (SIM800_DriverSIM800_Init(&Test_SIM800_Config) == SIM800_DriverRetVal_OK)
    {
        ESP_LOGI(tag, "SIM800 Init successful");
    }
    else
    {
        ESP_LOGE(tag, "SIM800 Init failed");
    }
}
