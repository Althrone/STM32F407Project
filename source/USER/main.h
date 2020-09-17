#include "stm32f4xx.h"
#include "i2c.h"

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
    extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
//基础通信协议
#include "usart.h"
#include "tim.h"
#include "iic_moni.h"
#include "ppm.h"

#include "ANO_DT.h"

#include "attitude.h"

#include "rgbled.h"
#include "motor.h"
//传感器
#include "mpu6050.h"
#include "spl06.h"
#include "ak8975.h"

#include "kalman.h"

#ifdef __cplusplus
}
#endif

#endif /*__MAIN_H */