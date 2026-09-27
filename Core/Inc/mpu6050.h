//
// Created by Hubert on 27.09.2026.
//

#ifndef AUTOPILOT_MPU6050_H
#define AUTOPILOT_MPU6050_H

#include "stm32f4xx_hal.h"

bool mpu6050_init(I2C_HandleTypeDef* i2c, uint16_t devAddr);

#endif //AUTOPILOT_MPU6050_H
