#include "Led.h"

Led::Led(GPIO_TypeDef *port, uint16_t pin) : _port(port), _pin(pin) {
}

void Led::on() {
    HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_SET);
}

void Led::off() {
    HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_RESET);
}

void Led::toggle() {
    HAL_GPIO_TogglePin(_port, _pin);
}
