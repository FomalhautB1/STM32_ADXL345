#include "adxl345.h"
#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

#define ADXL345_I2C_ADDR  (0x53 << 1)  // HAL использует 8-битный адрес (<<1)
#define ADXL345_DEVID_REG      0x53
#define ADXL345_DEVID_VALUE    0xE5

#define ADXL345_POWER_CTL      0x2D
#define ADXL345_INT_ENABLE     0x2E
#define ADXL345_INT_MAP        0x2F
#define ADXL345_DATA_FORMAT    0x31
#define ADXL345_BW_RATE        0x2C

// Инициализация ADXL345 (режим измерения)

HAL_StatusTypeDef ADXL345_WriteRegister(uint8_t reg, uint8_t value) {
    uint8_t data[2] = {reg, value};
    return HAL_I2C_Master_Transmit(&hi2c1, ADXL345_I2C_ADDR, data, 2, HAL_MAX_DELAY);
}

// Чтение одного байта из регистра
HAL_StatusTypeDef ADXL345_ReadRegister(uint8_t reg, uint8_t *value) {
    return HAL_I2C_Mem_Read(&hi2c1, ADXL345_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, value, 1, HAL_MAX_DELAY);
}

// Запись нескольких байт подряд в регистр (например, в FIFO или DATA_FORMAT)
HAL_StatusTypeDef ADXL345_WriteRegisters(uint8_t reg, uint8_t *values, uint8_t length) {
    uint8_t buffer[length + 1];
    buffer[0] = reg;
    for(uint8_t i = 0; i < length; i++) {
        buffer[i + 1] = values[i];
    }
    return HAL_I2C_Master_Transmit(&hi2c1, ADXL345_I2C_ADDR, buffer, length + 1, HAL_MAX_DELAY);
}

// Чтение нескольких байт подряд из регистра
HAL_StatusTypeDef ADXL345_ReadRegisters(uint8_t reg, uint8_t *buffer, uint8_t length) {
    return HAL_I2C_Mem_Read(&hi2c1, ADXL345_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, buffer, length, HAL_MAX_DELAY);
}


// Инициализация ADXL345 (режим измерения)
HAL_StatusTypeDef ADXL345_Init(void) {
    HAL_StatusTypeDef ret;
    uint8_t devid = 0;

    // Проверка Device ID (должен быть 0xE5)
    ret = ADXL345_ReadRegister(ADXL345_DEVID_REG, &devid);
    if (ret != HAL_OK) return ret;
    if (devid != ADXL345_DEVID_VALUE) return HAL_ERROR;

    // Устанавливаем частоту выборки (например, 100 Гц = 0x0A)
    ret = ADXL345_WriteRegister(ADXL345_BW_RATE, 0x0A);
    if (ret != HAL_OK) return ret;

    // Формат данных: полный режим (FULL_RES=1), диапазон ±2g
    ret = ADXL345_WriteRegister(ADXL345_DATA_FORMAT, 0x08);
    if (ret != HAL_OK) return ret;

    // Включаем прерывание "данные готовы"
    ret = ADXL345_WriteRegister(ADXL345_INT_ENABLE, 0x80);
    if (ret != HAL_OK) return ret;

    // Назначаем прерывание на INT1 (0x80 = DATA_READY -> INT1)
    ret = ADXL345_WriteRegister(ADXL345_INT_MAP, 0x00);
    if (ret != HAL_OK) return ret;

    // Включаем измерения (Measure=1)
    ret = ADXL345_WriteRegister(ADXL345_POWER_CTL, 0x08);
    if (ret != HAL_OK) return ret;

    return HAL_OK;
}

// ------------------------------------------------------------------
// Чтение акселерометра X, Y, Z
HAL_StatusTypeDef ADXL345_ReadAccel(float *x, float *y, float *z) {
    uint8_t rx[6] = {0};

    // Чтение 6 байт подряд: DATA_X0..DATA_Z1
    HAL_StatusTypeDef ret = ADXL345_ReadRegisters(0x32, rx, 6);
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

// ------------------------------------------------------------------
// Чтение ID чипа
HAL_StatusTypeDef ADXL345_ReadDEVID(uint8_t *devid) {
    // DEVID регистр = 0x00
    return ADXL345_ReadRegister(0x00, devid);
}

