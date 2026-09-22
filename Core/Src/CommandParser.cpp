#include <cstdio>
#include <cstring>

#include "AppState.h"
#include "LedMode.h"
#include "UartUtils.h"

extern "C" I2C_HandleTypeDef hi2c1;

void printLedMode() {
    uartPrint("Current Mode: ");
    uartPrint(ledModeMapper(getLedMode()));
    uartPrint("\r\n");
}

void handleCommand(const char* command) {
    if (strcmp(command, "/help") == 0) {
        uartPrint("Available commands:\r\n");
        uartPrint("/ping\r\n");
        uartPrint("/mode\r\n");
        uartPrint("/uptime\r\n");
        uartPrint("/reset\r\n");
        uartPrint("/modules\r\n");
        uartPrint("> ");
    } else if (strcmp(command, "/ping") == 0) {
        uartPrint("pong\r\n");
        uartPrint("> ");
    } else if (strcmp(command, "/mode") == 0) {
        printLedMode();
        uartPrint("Switching modes:\r\n");
        uartPrint("/mode off\r\n");
        uartPrint("/mode on\r\n");
        uartPrint("/mode slow\r\n");
        uartPrint("/mode fast\r\n");
        uartPrint("> ");
    } else if (strcmp(command, "/mode off") == 0) {
        setLedMode(LedMode::Off);
        printLedMode();
        uartPrint("> ");
    } else if (strcmp(command, "/mode on") == 0) {
        setLedMode(LedMode::On);
        printLedMode();
        uartPrint("> ");
    } else if (strcmp(command, "/mode slow") == 0) {
        setLedMode(LedMode::BlinkSlow);
        printLedMode();
        uartPrint("> ");
    } else if (strcmp(command, "/mode fast") == 0) {
        setLedMode(LedMode::BlinkFast);
        printLedMode();
        uartPrint("> ");
    } else if (strcmp(command, "/uptime") == 0) {
        uint32_t uptimeSeconds = HAL_GetTick() / 1000;

        char msg[64];
        snprintf(msg, sizeof(msg), "Uptime: %lu s\r\n", static_cast<unsigned long>(uptimeSeconds));

        uartPrint(msg);
        uartPrint("> ");
    } else if (strcmp(command, "/modules") == 0) {
        HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(&hi2c1, (0x68 << 1), 1, 100);
        if (ret == HAL_OK) {
            uartPrint("\rI2C: OK\r\n");
        } else {
            uartPrint("\rI2C: ERROR\r\n");
        }

        uartPrint("> ");
    } else if (strcmp(command, "/reset") == 0) {
        uartPrint("Resetting...\r\n");
        HAL_Delay(100);

        NVIC_SystemReset();
    } else {
        uartPrint("Command not found. Try /help for more information.\r\n");
        uartPrint("> ");
    }
}
