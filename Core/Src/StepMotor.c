/*
 * @Author: Tian Wei
 * @Date: 2021-11-15 13:48:27
 * @Description:
 * @Version: V1.0
 */
#include "StepMotor.h"
#include "tim.h"
#include "key.h"

__IO uint16_t Toggle_Pulse = 500; //

uint8_t dir = 1; // 0 ：下降  1：上升
uint8_t ena = 0; // 0 ：正常运行 1：停机
void StempMotorStateCtrol(void)
{
  uint8_t ucKeyCode;
  ucKeyCode = bsp_GetKey();
  if (ucKeyCode != KEY_NONE)
  {
    switch (ucKeyCode)
    {
    case KEY_1_DOWN:
      if (ena == 1)
      {
        MotorEnable(); // 正常运行
        TIM_CCxChannelCmd(TIM8, TIM_CHANNEL_1, TIM_CCx_ENABLE);
        ena = 0;
      }
      else
      {
        MotorDisable(); // 停机
        TIM_CCxChannelCmd(TIM8, TIM_CHANNEL_1, TIM_CCx_DISABLE);
        ena = 1;
      }
      break;
    case KEY_2_DOWN:
      if (dir == 0)
      {
        MotorDown();
        dir = 1;
      }
      else
      {
        MotorUp();
        dir = 0;
      }
      break;
    default:
      break;
    }
  }
}
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  __IO uint32_t count;
  __IO uint32_t tmp;
  count = __HAL_TIM_GET_COUNTER(&htim8);
  tmp = STEPMOTOR_TIM_PERIOD & (count + Toggle_Pulse);
  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, tmp);
}
