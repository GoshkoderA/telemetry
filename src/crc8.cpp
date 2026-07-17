#include "crc8.h"   // подключаем заголовок с объявлением функции

uint8_t crc8(const std::vector<uint8_t>& data) {
    uint8_t crc = 0x00;   // начальное значение

    for (uint8_t byte : data) {
        crc ^= byte;          // XOR с очередным байтом
        for (int i = 0; i < 8; ++i) {
            if (crc & 0x80)   // если старший бит = 1
                crc = (crc << 1) ^ 0x07;   // сдвиг + полином
            else
                crc <<= 1;    // просто сдвиг
        }
    }
    return crc;
}