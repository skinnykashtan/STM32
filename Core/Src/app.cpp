//
// Created by Hubert on 2.06.2026.
//

#include "app.h"
#include "Led.h"
#include "LedMode.h"
#include "Terminal.h"
#include "UartUtils.h"

extern "C" {
#include "main.h"
}

Led led(LD2_GPIO_Port, LD2_Pin);
LedMode led_mode = LedMode::Off;

LedMode getLedMode() {
    return led_mode;
}

void setLedMode(LedMode mode) {
    led_mode = mode;
}

volatile uint32_t lastCallback{};
volatile bool clickedButton = false;
extern volatile bool uartOverflow;

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    uint32_t now = HAL_GetTick();
    if (GPIO_Pin == B1_Pin && now - lastCallback >= 200) {
        clickedButton = true;
        lastCallback = now;
    }
}

uint32_t last_time;

void app_init(void) {
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
    HAL_Delay(200);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
    last_time = HAL_GetTick();
    terminalStartReceiveIT();
}

void app_loop(void) {

    terminalProcess();
    if (uartOverflow) {
        uartOverflow = false;
        uartPrint("\r\nUART RX buffer overflow\r\n");
    }

    if (clickedButton) {
        clickedButton = false;
        led_mode = nextMode(led_mode);
        sendDebugMessage(led_mode);
    }

    updateLed(led, last_time);
}
