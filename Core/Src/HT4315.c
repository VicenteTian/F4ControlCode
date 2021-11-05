/*
 * @Author: Tian Wei
 * @Date: 2021-11-05 20:01:54
 * @Description:
 * @Version: V1.0
 */
#include "HT4315.h"
uint8_t RS485TxBuff[20] = {0};
uint8_t RS485RxBuff[20] = {0};

const uint16_t crctalbeabs[] = {
    0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 0x3C00, 0x2800, 0xE401,
    0xA001, 0x6C00, 0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 0x4400};
uint16_t CRC16_MODBUS(uint8_t *Buff, uint8_t len)
{
    uint16_t crc = 0xffff;
    uint16_t i;
    uint8_t ch;
    for (i = 0; i < len; i++)
    {
        ch = *Buff++;
        crc = crctalbeabs[(ch ^ crc) & 15] ^ (crc >> 4);
        crc = crctalbeabs[((ch >> 4) ^ crc) & 15] ^ (crc >> 4);
    }
    return crc;
}
HAL_StatusTypeDef RS485Trans(uint8_t sequence, uint8_t slaver_addr, uint8_t cmd, uint8_t data_len, uint8_t *data)
{
    RS485TxBuff[0] = MasterHeader;
    RS485TxBuff[1] = sequence;
    RS485TxBuff[2] = slaver_addr;
    RS485TxBuff[3] = cmd;
    RS485TxBuff[4] = data_len;
    for (uint8_t i = 0; i < data_len; i++)
    {
        RS485TxBuff[5 + i] = data[i];
    }
    uint16_t crc16 = CRC16_MODBUS(RS485TxBuff, 5 + data_len);
    RS485TxBuff[5 + data_len] = (uint8_t)crc16;
    RS485TxBuff[6 + data_len] = (uint8_t)(crc16 >> 8);
    RS458DE;
    return HAL_UART_Transmit(&huart3, RS485TxBuff, 7 + data_len, 50);
}
void set_Motor_angle(int16_t angle)
{
    uint8_t data[4] = {0};
    int32_t count = angle * 16384 / 360;
    data[0] = (uint8_t)count;
    data[1] = (uint8_t)(count >> 8);
    data[2] = (uint8_t)(count >> 16);
    data[3] = (int8_t)(count >> 24);
    RS485Trans(0, Motor2, MotorPosCtrl, 4, data);
    RS458RE;
}
