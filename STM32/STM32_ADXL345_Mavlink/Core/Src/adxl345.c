#include "adxl345.h"
#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

#define ADXL345_I2C_ADDR  (0x53 << 1)  // HAL использует 8-битный адрес (<<1)

// Инициализация ADXL345 (режим измерения)
HAL_StatusTypeDef ADXL345_Init(void) {
    uint8_t data[2];

    data[0] = 0x2D;   // POWER_CTL register
    data[1] = 0x08;   // Measure mode
    return HAL_I2C_Master_Transmit(&hi2c1, ADXL345_I2C_ADDR, data, 2, HAL_MAX_DELAY);
}

// Чтение акселерометра X, Y, Z
HAL_StatusTypeDef ADXL345_ReadAccel(float *x, float *y, float *z) {
    uint8_t reg = 0x32; // DATA_X0 register
    uint8_t rx[6] = {0};

    // Чтение 6 байт подряд: X0,X1,Y0,Y1,Z0,Z1
    HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(&hi2c1, ADXL345_I2C_ADDR, &reg, 1, HAL_MAX_DELAY);
    if(ret != HAL_OK) return ret;

    ret = HAL_I2C_Master_Receive(&hi2c1, ADXL345_I2C_ADDR, rx, 6, HAL_MAX_DELAY);
    if(ret != HAL_OK) return ret;

    int16_t raw_x = (rx[1] << 8) | rx[0];
    int16_t raw_y = (rx[3] << 8) | rx[2];
    int16_t raw_z = (rx[5] << 8) | rx[4];

    float scale = 0.0039f * 9.81f; // ±2g
    *x = raw_x * scale;
    *y = raw_y * scale;
    *z = raw_z * scale;

    return HAL_OK;
}

// Чтение ID чипа
HAL_StatusTypeDef ADXL345_ReadDEVID(uint8_t *devid) {
    uint8_t reg = 0x53; // DEVID register
    return HAL_I2C_Mem_Read(&hi2c1, ADXL345_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, devid, 1, HAL_MAX_DELAY);
}
