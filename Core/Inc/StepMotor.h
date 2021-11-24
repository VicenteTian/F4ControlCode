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

#define MAX_SPEED 1000
#define MIN_SPEED 1
#define abs(x) ((x) < 0 ? (-x) : (x))
#define SAMPLING_PERIOD 25 // 力传感器采样周期 单位ms
#define FREQ_UINT 6000     // SystemCoreClock/((Prescaler+1)*2*50)

#define MotorUp() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET)
#define MotorDown() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET)

#define MotorEnable() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET)
#define MotorDisable() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET)
void PID_init(void);
int16_t GetSetForce(void);
void SetPIDForce(int16_t setForce);
void StempMotorPIDCtrol(int16_t RealForce);
void STEPMOTOR_Motion_Ctrl(uint8_t Dir, float Frequency);
void StempMotorStateCtrol(void);

#define STEPMOTOR_TIM_PERIOD 0xFFFF

#endif /* __STEPMOTOR_TIM_H__ */
