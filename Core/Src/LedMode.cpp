//
// Created by Hubert on 6.06.2026.
//

#include "LedMode.h"
#include "UartUtils.h"

const char* ledModeMapper(LedMode led_mode) {
    switch (led_mode) {
        case LedMode::Off:
            return "Off";
        case LedMode::On:
            return "On";
        case LedMode::BlinkSlow:
            return "Slow";
        case LedMode::BlinkFast:
            return "Fast";
        case LedMode::Message:
            return "Message receiver ON";
    }

    return "Unknown";
}

void updateLed(LedMode led_mode, Led& led, uint32_t& last_time) {
    constexpr uint32_t intervalSlow = 1000;
    constexpr uint32_t intervalFast = 100;
    uint32_t now = HAL_GetTick();
    uint8_t rxByte;
    static uint8_t index=0;
    static char rxBuffer[64];

    switch (led_mode) {
        case LedMode::Off:
            led.off();
            break;
        case LedMode::On:
            led.on();
            break;
        case LedMode::BlinkSlow:
            if (now-last_time>=intervalSlow) {
                last_time = now;
                led.toggle();
            }
            break;
        case LedMode::BlinkFast:
            if (now-last_time>=intervalFast) {
                last_time = now;
                led.toggle();
            }
            break;
        case LedMode::Message:
            if (HAL_UART_Receive(&huart2, &rxByte, 1, 0) == HAL_OK) {
                if (rxByte == '\r' || rxByte == '\n') {
                    rxBuffer[index] = '\0';
                    uartPrint("\r\n");
                    index = 0;
                } else if (index < sizeof(rxBuffer) - 1) {
                    rxBuffer[index] = rxByte;
                    index++;

                    HAL_UART_Transmit(&huart2, &rxByte, 1, 100);
                }
            }
            break;
        default:
            led.off();
            sendDebugMessage(LedMode::Off);
            break;
    }
}

LedMode nextMode(LedMode current) {
    switch (current) {
        case LedMode::Off:
            return LedMode::On;
        case LedMode::On:
            return LedMode::BlinkSlow;
        case LedMode::BlinkSlow:
            return LedMode::BlinkFast;
        case LedMode::BlinkFast:
            return LedMode::Message;
        case LedMode::Message:
            return LedMode::Off;
    }

    return LedMode::Off;
}