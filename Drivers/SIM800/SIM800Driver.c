#include "SIM800Driver.h"

SIM800_DriverRetVal_e SIM800_DriverSIM800_Init(SIM800_DriverSIM800Config_s *pSIM800Modem_i)
{
    SIM800_DriverRetVal_e driverRetVal;
    GPIO_DriverRetVal_e GPIO_DriverRetVal;
    driverRetVal = SIM800_DriverRetVal_OK;
    gpioDriverPinInit_Output(&(pSIM800Modem_i->Pin_PWKEY));
    gpioDriverPinInit_Output(&(pSIM800Modem_i->Pin_RST));
    gpioDriverPinInit_Output(&(pSIM800Modem_i->Pin_POWERON));
    return driverRetVal;
}
