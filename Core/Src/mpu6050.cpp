#include "stm32f4xx_hal.h"

bool mpu6050_init(I2C_HandleTypeDef* i2c, uint16_t devAddr) {
    uint16_t hal_addr = devAddr << 1;
    if (HAL_I2C_IsDeviceReady(i2c, hal_addr, 1, 100) != HAL_OK) {
        return false;
    }

    uint8_t pwr = 0;
    HAL_StatusTypeDef pwr_cfg = HAL_I2C_Mem_Write(i2c, hal_addr, 0x6B, I2C_MEMADD_SIZE_8BIT, &pwr, 1, 100);
    if (pwr_cfg != HAL_OK) {
        return false;
    }

    uint8_t FS_SEL = 0x08;
    HAL_StatusTypeDef gyro_cfg = HAL_I2C_Mem_Write(i2c, hal_addr, 0x1B,I2C_MEMADD_SIZE_8BIT, &FS_SEL, 1, 100);

    if (gyro_cfg != HAL_OK) {
        return false;
    }

    return true;
}
