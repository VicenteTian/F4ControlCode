#include "StepMotor.h"
#include "tim.h"

__IO uint16_t Toggle_Pulse = 3000;         // 
__IO uint32_t pulse_count = 0;


void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  __IO uint32_t count;
  __IO uint32_t tmp;
  count =__HAL_TIM_GET_COUNTER(&htim8);
  tmp = STEPMOTOR_TIM_PERIOD & (count+Toggle_Pulse);
  __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,tmp);
  pulse_count++;
}

