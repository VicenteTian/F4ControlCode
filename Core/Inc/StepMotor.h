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

#define MAX_SPEED 600
#define MIN_SPEED 10
#define abs(x) ((x) < 0 ? (-x) : (x))
#define T1_FREQ 16000
#define SAMPLING_PERIOD 25                    // 力传感器采样周期 单位ms
#define FREQ_UINT (T1_FREQ * SAMPLING_PERIOD) //对定时器的频率做单位换算,避免数值太大溢出

#define MotorUp() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET)
#define MotorDown() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET)

#define MotorEnable() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET)
#define MotorDisable() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET)
void PID_init(void);
void SetPIDForce(int16_t setForce);
void StempMotorPIDCtrol(int16_t RealForce);
void STEPMOTOR_Motion_Ctrl(uint8_t Dir, float Frequency);
void StempMotorStateCtrol(void);

#define STEPMOTOR_TIM_PERIOD 0xFFFF

#endif /* __STEPMOTOR_TIM_H__ */
