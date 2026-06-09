//
// Created by Hubert on 6.06.2026.
//

#ifndef AUTOPILOT_UARTUTILS_H
#define AUTOPILOT_UARTUTILS_H

#include "LedMode.h"

void sendDebugMessage(LedMode led_mode);
void uartPrint(const char* text);
void uartPoll();

#endif //AUTOPILOT_UARTUTILS_H
