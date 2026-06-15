//
// Created by Hubert on 15.06.2026.
//

#include "RingBuffer.h"

bool RingBuffer::push(uint8_t byte) {
    std::size_t nextHead = (head + 1) % bufferSize;

    if (nextHead == tail) {
        return false;
    }
    ringBuffer[head] = byte;
    head = nextHead;

    return true;
}

bool RingBuffer::pop(uint8_t& byte) {
    if (head == tail) {
        return false;
    }
    byte = ringBuffer[tail];
    tail = (tail + 1) % bufferSize;

    return true;
}