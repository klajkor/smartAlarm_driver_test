/* UART asynchronous example, that uses separate RX and TX tasks

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "uartDriver_test.h"

static const char tag[] = "uartDriver Test";

static const int RX_BUF_SIZE = 1024;
static const int TEST_UART_NUM = UART_NUM_2;

UART_DriverUARTConfig_s UART2_config = {.UART_number = TEST_UART_NUM,
                                        .UART_baud_rate = 115200,
                                        .UART_data_bits = UART_DATA_8_BITS,
                                        .UART_stop_bits = UART_STOP_BITS_1,
                                        .UART_parity = UART_PARITY_DISABLE,
                                        .UART_TxBuff_Size = STD_UART_BUF_SIZE,
                                        .UART_RxBuff_Size = STD_UART_BUF_SIZE,
                                        .UART_TxGPIO_Pin = GPIO_NUM_27,
                                        .UART_RxGPIO_Pin = GPIO_NUM_26};

void uart_init(void)
{

    if (UART_DriverUARTInit(&UART2_config) == UART_DriverRetVal_OK)
    {
        ESP_LOGI(tag, "UART Init successful");
    }
    else
    {
        ESP_LOGE(tag, "UART Init failed");
    }
}

int uart_sendData(const char *logName, const char *data)
{
    const int len = strlen(data);
    const int txBytes = uart_write_bytes(TEST_UART_NUM, data, len);
    ESP_LOGI(logName, "Wrote %d bytes", txBytes);
    return txBytes;
}

void uart_tx_task(void *arg)
{
    static const char *TX_TASK_TAG = "TX_TASK";
    esp_log_level_set(TX_TASK_TAG, ESP_LOG_INFO);
    while (1)
    {
        UART_DriverSendByte(&UART2_config, 0x31);
        UART_DriverSendByte(&UART2_config, 0x10);
        //uart_sendData(TX_TASK_TAG, "Hello world");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void uart_rx_task(void *arg)
{
    static const char *RX_TASK_TAG = "RX_TASK";
    int rxBytes;
    size_t buf_ok;
    uint32_t cnt = 0;
    esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
    uint8_t *data = (uint8_t *)malloc(RX_BUF_SIZE + 1);
    while (1)
    {
        ESP_ERROR_CHECK(uart_get_buffered_data_len(TEST_UART_NUM, &buf_ok));
        if (buf_ok > 0)
        {
            ESP_LOGI(RX_TASK_TAG, "read Begin");
            rxBytes = uart_read_bytes(TEST_UART_NUM, data, buf_ok, 1000 / portTICK_RATE_MS);
            if (rxBytes > 0)
            {
                data[rxBytes] = 0;
                ESP_LOGI(RX_TASK_TAG, "Read %d(%d) bytes: '%s'", rxBytes, buf_ok, data);
                ESP_LOG_BUFFER_HEXDUMP(RX_TASK_TAG, data, rxBytes, ESP_LOG_INFO);
            }
            ESP_LOGI(RX_TASK_TAG, "Recv Task cnt=%d.", cnt);
        }
        cnt++;
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    free(data);
}

void run_uart_tests(void)
{
    uart_init();
    vTaskDelay(100 / portTICK_PERIOD_MS);

    xTaskCreate(uart_rx_task, "uart_rx_task", 1024 * 2, NULL, configMAX_PRIORITIES, NULL);
    xTaskCreate(uart_tx_task, "uart_tx_task", 1024 * 2, NULL, configMAX_PRIORITIES - 1, NULL);
}
