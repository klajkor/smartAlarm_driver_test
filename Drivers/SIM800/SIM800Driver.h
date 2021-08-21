/*
* SIM800 Driver for smartAlarm system
*/

#pragma once

#include <stdio.h>
#include "gpioDriver.h"
#include "uartDriver.h"

typedef enum
{
    SIM800_DriverRetVal_OK = 0,
    SIM800_DriverRetVal_NOK,
    SIM800_DriverRetVal_End
} SIM800_DriverRetVal_e;

typedef struct
{
    GPIO_DriverGPIOConfig_s Pin_PWKEY;
    GPIO_DriverGPIOConfig_s Pin_RST;
    GPIO_DriverGPIOConfig_s Pin_POWERON;
    UART_DriverUARTConfig_s SIM800_UART;
} SIM800_DriverSIM800Config_s;

SIM800_DriverRetVal_e SIM800_DriverSIM800_Init(SIM800_DriverSIM800Config_s *pSIM800Modem_i);
