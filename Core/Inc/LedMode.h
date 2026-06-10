//
// Created by Hubert on 6.06.2026.
//
#pragma once

#include "Led.h"

enum class LedMode {
    Off,
    On,
    BlinkSlow,
    BlinkFast
};

const char* ledModeMapper(LedMode led_mode);

void updateLed(Led& led, uint32_t& last_time);

LedMode nextMode(LedMode current);

