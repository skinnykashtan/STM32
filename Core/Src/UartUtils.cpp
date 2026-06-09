//
// Created by Hubert on 6.06.2026.
//

#include <cstdio>
#include <cstring>
#include "UartUtils.h"

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
