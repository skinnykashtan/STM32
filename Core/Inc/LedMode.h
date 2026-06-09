//
// Created by Hubert on 6.06.2026.
//
#pragma once

#include "Led.h"

enum class LedMode {
    Off,
    On,
    BlinkSlow,
    BlinkFast,
    Message
};

const char* ledModeMapper(LedMode led_mode);

void updateLed(LedMode led_mode, Led& led, uint32_t& last_time);

LedMode nextMode(LedMode current);

