/*
 * @Author: Tian Wei
 * @Date: 2021-11-15 13:48:15
 * @Description:
 * @Version: V1.0
 */
#ifndef __STEPMOTOR_H__
#define __STEPMOTOR_H__

//包含头文件
#include "stm32f4xx_hal.h"
#define SAMPLING_PERIOD 25 // 力传感器采样周期 单位ms
#define TXDCYCLE 50      // 数据发送周期;单位：ms
#define SAMPLING 0x01      // 采样标记
#define TXD 0x02           // 发送数据标记

#define MotorUp() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET)
#define MotorDown() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET)

#define MotorEnable() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET)
#define MotorDisable() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET)
void StempMotorStateCtrol(void);

#define STEPMOTOR_TIM_PERIOD 0xFFFF

#endif /* __STEPMOTOR_TIM_H__ */
