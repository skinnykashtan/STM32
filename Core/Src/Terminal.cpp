#include "Terminal.h"

#include <cstdio>
#include <cstring>
#include "AppState.h"
#include "UartUtils.h"

void handleCommand(const char* command) {
    if (strcmp(command, "/help") == 0) {
        uartPrint("Available commands:\r\n");
        uartPrint("/ping\r\n");
        uartPrint("/mode\r\n");
        uartPrint("/uptime\r\n");
        uartPrint("/reset\r\n");
        uartPrint("> ");
    } else if (strcmp(command, "/ping") == 0) {
        uartPrint("pong\r\n");
        uartPrint("> ");
    } else if (strcmp(command, "/mode") == 0) {
        uartPrint("Current Mode: ");
        uartPrint(ledModeMapper(getLedMode()));
        uartPrint("\r\n");
        uartPrint("> ");
    } else if (strcmp(command, "/uptime") == 0) {
        uint32_t uptimeSeconds = HAL_GetTick() / 1000;

        char msg[64];
        snprintf(msg, sizeof(msg), "Uptime: %lu s\r\n", static_cast<unsigned long>(uptimeSeconds));

        uartPrint(msg);
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