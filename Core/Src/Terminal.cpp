#include "Terminal.h"

#include <cstdio>
#include <cstring>
#include "AppState.h"
#include "UartUtils.h"
#include "CommandParser.h"

extern "C" UART_HandleTypeDef huart2;

static void handleReceivedByte(uint8_t rxByte);

static uint8_t rxByte{};

static char rxBuffer[64]{};
static uint8_t rxIndex{};

static volatile bool commandReady = false;
static char commandBuffer[64]{};

void terminalStartReceiveIT() {
    HAL_UART_Receive_IT(&huart2, &rxByte, 1);
}

extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
    if (huart->Instance == USART2) {
        handleReceivedByte(rxByte);

        HAL_UART_Receive_IT(&huart2, &rxByte, 1);
    }
}

void terminalProcess() {
    if (commandReady) {
        commandReady = false;
        handleCommand(commandBuffer);
    }
}

static void handleReceivedByte(uint8_t rxByte) {
    if (rxByte == '\r' || rxByte == '\n') {
        rxBuffer[rxIndex] = '\0';

        if (rxIndex > 0 && !commandReady) {
            uartPrint("\r\n");
            strncpy(commandBuffer, rxBuffer, sizeof(commandBuffer));
            commandBuffer[sizeof(commandBuffer) - 1] = '\0';

            commandReady = true;
        }

        rxIndex = 0;
    } else if (rxByte == '\b' || rxByte == 127) {
        if (rxIndex > 0) {
            rxIndex--;

            uartPrint("\b \b");
        }
    } else if (rxIndex < sizeof(rxBuffer) - 1) {
        rxBuffer[rxIndex] = rxByte;
        rxIndex++;

        HAL_UART_Transmit(&huart2, &rxByte, 1, 100);
    } else {
        uartPrint("\r\nCommand too long\r\n");
        rxIndex = 0;
    }
}