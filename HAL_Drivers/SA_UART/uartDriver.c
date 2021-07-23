#include "uartDriver.h"

static const char tag[] = "HAL uartDriver";

UART_DriverRetVal_e UART_DriverUARTInit(UART_DriverUARTConfig_s *pUARTPeripheral_i)
{
    UART_DriverRetVal_e ret_val;
    esp_err_t esp_ret_val;
    uart_config_t driver_uart_config = {
        .baud_rate = pUARTPeripheral_i->UART_baud_rate,
        .data_bits = pUARTPeripheral_i->UART_data_bits,
        .parity = pUARTPeripheral_i->UART_parity,
        .stop_bits = pUARTPeripheral_i->UART_stop_bits,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
    };
    ret_val = UART_DriverRetVal_OK;
    esp_ret_val = uart_param_config(pUARTPeripheral_i->UART_number, &driver_uart_config);
    if (esp_ret_val != ESP_OK)
    {
        ret_val = UART_DriverRetVal_NOK;
        ESP_LOGE(tag, "uart_param_config() error");
    }
    if (ret_val == UART_DriverRetVal_OK)
    {
        esp_ret_val = uart_set_pin(pUARTPeripheral_i->UART_number, pUARTPeripheral_i->UART_TxGPIO_Pin, pUARTPeripheral_i->UART_RxGPIO_Pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
        if (esp_ret_val != ESP_OK)
        {
            ret_val = UART_DriverRetVal_NOK;
            ESP_LOGE(tag, "uart_set_pin() error");
        }
    }

    if (ret_val == UART_DriverRetVal_OK)
    {
        esp_ret_val = uart_driver_install(pUARTPeripheral_i->UART_number, pUARTPeripheral_i->UART_RxBuff_Size, pUARTPeripheral_i->UART_TxBuff_Size, 0, NULL, 0);
        if (esp_ret_val != ESP_OK)
        {
            ret_val = UART_DriverRetVal_NOK;
            ESP_LOGE(tag, "uart_driver_install() error");
        }
    }
    return ret_val;
}

UART_DriverRetVal_e UART_DriverSendByte(UART_DriverUARTConfig_s *pUARTPeripheral_i, uint8_t data_i)
{
    UART_DriverRetVal_e ret_val;
    char data_to_be_sent[2];
    int sent_bytes;
    data_to_be_sent[0] = data_i;
    data_to_be_sent[1] = 0;
    ret_val = UART_DriverRetVal_OK;
    sent_bytes = uart_write_bytes(pUARTPeripheral_i->UART_number, data_to_be_sent, 1);
    if (sent_bytes < 1)
    {
        ret_val = UART_DriverRetVal_NOK;
    }
    return ret_val;
}
