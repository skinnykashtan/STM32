//
// Created by Hubert on 15.06.2026.
//

#ifndef AUTOPILOT_RINGBUFFER_H
#define AUTOPILOT_RINGBUFFER_H
#include <cstddef>
#include <cstdint>

class RingBuffer {
private:
    char ringBuffer[128];
    std::size_t head{};
    std::size_t tail{};
    const uint8_t bufferSize = 128;
public:
    RingBuffer() = default;

    bool push(uint8_t byte);

    bool pop(uint8_t& byte);
};

#endif //AUTOPILOT_RINGBUFFER_H
