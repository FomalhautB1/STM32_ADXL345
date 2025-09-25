/*
 * adxl345.h
 *
 *  Created on: Sep 24, 2025
 *      Author: bdfy
 */

#ifndef INC_ADXL345_H_
#define INC_ADXL345_H_

#include "stm32f4xx_hal.h"

HAL_StatusTypeDef ADXL345_WriteRegister(uint8_t reg, uint8_t value);

// Чтение одного байта из регистра
HAL_StatusTypeDef ADXL345_ReadRegister(uint8_t reg, uint8_t *value);

// Запись нескольких байт подряд в регистр (например, в FIFO или DATA_FORMAT)
HAL_StatusTypeDef ADXL345_WriteRegisters(uint8_t reg, uint8_t *values, uint8_t length);

// Чтение нескольких байт подряд из регистра
HAL_StatusTypeDef ADXL345_ReadRegisters(uint8_t reg, uint8_t *buffer, uint8_t length);

// Инициализация ADXL345 (Measure mode)
HAL_StatusTypeDef ADXL345_Init(void);

// Чтение ускорений по осям X, Y, Z (в м/с²)
HAL_StatusTypeDef ADXL345_ReadAccel(float *x, float *y, float *z);

// Чтение ID чипа (ожидаемый 0xE5)
HAL_StatusTypeDef ADXL345_ReadDEVID(uint8_t *devid);

#endif /* INC_ADXL345_H_ */


