#pragma once
#include <cstdint>
#include <vector>
#include <functional>

class FrameReceiver {
public:
    using FrameCallback = std::function<void(uint8_t type, const std::vector<uint8_t>& payload)>;

    explicit FrameReceiver(FrameCallback callback);

    // Подать один байт из потока
    void feed(uint8_t byte);

    // Сбросить состояние 
    void reset();

private:
    enum State {
        WAITING_STX,
        READING_LEN,
        READING_PAYLOAD,
        READING_CRC
    };

    State state_ = WAITING_STX;
    FrameCallback callback_;

    uint8_t len_ = 0;
    uint8_t type_ = 0;
    std::vector<uint8_t> payload_;
    uint8_t crc_received_ = 0;

    void processFrame();
};