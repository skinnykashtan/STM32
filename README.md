# STM32

A small project I work on in my free time to learn how STM32 microcontrollers work.

The project is still in development. At the moment, it contains a simple UART terminal for the NUCLEO-F446RE board. The terminal can be used to control the onboard LED, check the board uptime, test the connection and reset the microcontroller.

## Current features

- UART terminal using USART2
- interrupt-driven UART reception
- custom ring buffer for received bytes
- command input with echo and backspace support
- LED modes: off, on, slow blink and fast blink
- button interrupt for switching between LED modes
- basic software debouncing
- handling of long commands and UART buffer overflow

## Commands

```text
/help        displays available commands
/ping        responds with pong
/mode        displays the current LED mode and available options
/mode off    turns the LED off
/mode on     turns the LED on
/mode slow   enables slow blinking
/mode fast   enables fast blinking
/uptime      displays the time since startup
/reset       resets the microcontroller
```

## Hardware

- NUCLEO-F446RE
- STM32F446RE microcontroller
- onboard LD2 LED
- onboard B1 user button

## Technologies

- C and C++
- STM32 HAL
- STM32CubeMX
- CMake

## UART settings

```text
Baud rate: 115200
Data bits: 8
Stop bits: 1
Parity: none
Flow control: none
```

## Status

This is a learning project, so I add and change things as I learn more about STM32, interrupts and peripheral communication.

