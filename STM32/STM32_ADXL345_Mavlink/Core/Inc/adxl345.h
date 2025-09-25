/*
 * adxl345.h
 *
 *  Created on: Sep 24, 2025
 *      Author: bdfy
 */

#ifndef INC_ADXL345_H_
#define INC_ADXL345_H_

#include "stm32f4xx_hal.h"

// Инициализация ADXL345 (Measure mode)
HAL_StatusTypeDef ADXL345_Init(void);

// Чтение ускорений по осям X, Y, Z (в м/с²)
HAL_StatusTypeDef ADXL345_ReadAccel(float *x, float *y, float *z);

// Чтение ID чипа (ожидаемый 0xE5)
HAL_StatusTypeDef ADXL345_ReadDEVID(uint8_t *devid);

#endif /* INC_ADXL345_H_ */


