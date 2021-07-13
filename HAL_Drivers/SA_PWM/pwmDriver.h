/**
* PWM driver for smartAlarm system
*/

#pragma once

#include <stdio.h>
#include "driver/ledc.h"

typedef enum
{
    PWM_DriverRetVal_OK = 0,
    PWM_DriverRetVal_NOK,
    PWM_DriverRetVal_End
} PWM_DriverRetVal_e;

typedef enum
{
    PWM_DriverPinPWMStatus_Enabled = 0,
    PWM_DriverPinPWMStatus_Disabled,
    PWM_DriverPinPWMStatus_End
} PWM_DriverPinPWMStatus_e;

typedef struct
{
    uint32_t PWM_DriverPin;
    uint32_t PWM_DriverFrequency; /* in Hertz */
    uint8_t PWM_DriverDuty;       /* in percent 0-100 */
    PWM_DriverPinPWMStatus_e PWM_DriverPinPWMStatus;
} PWM_DriverPinConfig_s;

typedef enum
{
    PWM_Driver_Pin0 = 0,
    PWM_Driver_Pin1,
    PWM_Driver_Pin_End
} PWM_DriverPinList_e;

PWM_DriverPinConfig_s smartAlarmPWMPinList[PWM_Driver_Pin_End] = {
    {.PWM_DriverPin = GPIO_NUM_26,
     .PWM_DriverFrequency = 2,
     .PWM_DriverDuty = 25,
     .PWM_DriverPinPWMStatus = PWM_DriverPinPWMStatus_Disabled},

};

PWM_DriverRetVal_e PWM_DriverInitPin(PWM_DriverPinConfig_s *pPWMPin_i);
PWM_DriverRetVal_e PWM_DriverDeInitPin(PWM_DriverPinConfig_s *pPWMPin_i);
PWM_DriverRetVal_e PWM_DriverSetDuty(PWM_DriverPinConfig_s *pPWMPin_i);
PWM_DriverRetVal_e PWM_DriverSetFrequency(PWM_DriverPinConfig_s *pPWMPin_i);
PWM_DriverRetVal_e PWM_DriverEnablePWM(PWM_DriverPinConfig_s *pPWMPin_i);
PWM_DriverRetVal_e PWM_DriverDisablePWM(PWM_DriverPinConfig_s *pPWMPin_i);
//PWM_DriverRetVal_e PWM_DriverInit(void);
//PWM_DriverRetVal_e PWM_DriverDeInit(void);
//PWM_DriverRetVal_e PWM_DriverGetPinPWMStatus(PWM_DriverPinConfig_s *pPWMPin_i);
//PWM_DriverRetVal_e PWM_DriverGetParameters(PWM_DriverPinList_e PWM_DriverPin_i);
