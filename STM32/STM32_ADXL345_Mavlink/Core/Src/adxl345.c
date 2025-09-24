/*
 * adxl345.c
 *
 *  Created on: Sep 24, 2025
 *      Author: bdfy
 */


#include "adxl345.h"

extern SPI_HandleTypeDef hspi1;

static void ADXL345_CS(uint8_t state) {
    HAL_GPIO_WritePin(ADXL345_CS_PORT, ADXL345_CS_PIN, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void ADXL345_Init(void) {
    uint8_t data = 0x08; // Measure mode
    ADXL345_CS(0);
    uint8_t addr = 0x2D; // POWER_CTL
    HAL_SPI_Transmit(ADXL345_SPI, &addr, 1, 100);
    HAL_SPI_Transmit(ADXL345_SPI, &data, 1, 100);
    ADXL345_CS(1);
}

void ADXL345_ReadAccel(float *x, float *y, float *z) {
    uint8_t rx[6], tx[6];
    uint8_t addr = 0x32 | 0x80; // DATA_X0 register + read bit
    ADXL345_CS(0);
    HAL_SPI_Transmit(ADXL345_SPI, &addr, 1, 100);
    HAL_SPI_Receive(ADXL345_SPI, rx, 6, 100);
    ADXL345_CS(1);

    int16_t raw_x = (rx[1]<<8) | rx[0];
    int16_t raw_y = (rx[3]<<8) | rx[2];
    int16_t raw_z = (rx[5]<<8) | rx[4];

    float scale = 0.0039f*9.81f; // для ±2g
    *x = raw_x * scale;
    *y = raw_y * scale;
    *z = raw_z * scale;
}
