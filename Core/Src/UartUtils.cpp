//
// Created by Hubert on 6.06.2026.
//

#include <cstdio>
#include <cstring>
#include "UartUtils.h"

#include "Terminal.h"

extern "C" {
#include "main.h"
}

void sendDebugMessage(LedMode led_mode) {
    char msg[64];

    int len = snprintf(msg, sizeof(msg), "Button mode: %s\r\n", ledModeMapper(led_mode));

    if (len > 0) {
        HAL_UART_Transmit(&huart2, reinterpret_cast<uint8_t*>(msg), static_cast<uint16_t>(len), 100);
    }
}

void uartPrint(const char* text) {
    HAL_UART_Transmit(&huart2, reinterpret_cast<uint8_t*>(const_cast<char*>(text)), strlen(text), 100);
}

void uartPoll() {
    static char rxBuffer[64];
    static uint8_t index = 0;
    uint8_t rxByte;

    if (HAL_UART_Receive(&huart2, &rxByte, 1, 0) == HAL_OK) {
        if (rxByte == '\r' || rxByte == '\n') {
            rxBuffer[index] = '\0';

            if (index > 0) {
                uartPrint("\r\n");
                handleCommand(rxBuffer);
            }

            index = 0;
        } else if (rxByte == '\b' || rxByte == 127) {
            if (index > 0) {
                index--;

                uartPrint("\b \b");
            }
        } else if (index < sizeof(rxBuffer) - 1) {
            rxBuffer[index] = rxByte;
            index++;

            HAL_UART_Transmit(&huart2, &rxByte, 1, 100);
        } else {
            uartPrint("\r\nCommand too long\r\n");
            index = 0;
        }
    }
}
