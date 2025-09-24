/*
 * adxl345.h
 *
 *  Created on: Sep 24, 2025
 *      Author: bdfy
 */

#ifndef INC_ADXL345_H_
#define INC_ADXL345_H_

#ifndef ADXL345_H
#define ADXL345_H

#include "stm32f4xx_hal.h"

#define ADXL345_SPI &hspi1
#define ADXL345_CS_PIN ADXL345_CS_Pin
#define ADXL345_CS_PORT GPIOA

void ADXL345_Init(void);
void ADXL345_ReadAccel(float *x, float *y, float *z);

#endif

#endif /* INC_ADXL345_H_ */
