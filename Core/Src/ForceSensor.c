/*
 * @Author: Tian Wei
 * @Date: 2021-11-16 13:00:42
 * @Description:
 * @Version: V1.0
 */
#include "ForceSensor.h"
void getSensor(void)
{
    uint8_t sensorCmd[8] = {0x01U, 0x03U, 0U, 0U, 0U, 0x1U, 0x84U, 0x0aU};
    HAL_UART_Transmit(&huart5, (uint8_t *)sensorCmd, 8, 50);
}
void vParseSensor(uint8_t is_send)
{
    int16_t force = 0;
    force |= rx_buffer2[3];
    force <<= 8;
    force |= rx_buffer2[4];//单位0.1N，实际的力为force*0.1N=force*10g/1kg*10N/kg
    vcan_sendware((uint8_t *)&force, sizeof(force));
}
void restartRev2(void)
{
    memset(rx_buffer2, 0, rx_len2);
    rx_len2 = 0;                                  //清除计数
    recv_end_flag2 = 0;                           //清除接收结束标志
    HAL_UART_Receive_DMA(&huart5, rx_buffer2, 8); //重新打开DMA接收
}
