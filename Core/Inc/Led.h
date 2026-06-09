//
// Created by Hubert on 6.06.2026.
//

#ifndef AUTOPILOT_LEDMODE_H
#define AUTOPILOT_LEDMODE_H

#include "main.h"

class Led {
private:
    GPIO_TypeDef* _port;
    uint16_t _pin;
public:
    Led(GPIO_TypeDef* port, uint16_t pin);

    void on();

    void off();

    void toggle() ;
};


#endif //AUTOPILOT_LEDMODE_H
