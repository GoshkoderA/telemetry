#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "crc8.h"

// пустой вектор, CRC = 0x00
TEST(CRC8Test, EmptyData) {
    std::vector<uint8_t> data;
    EXPECT_EQ(crc8(data), 0x00);
}

// известный вектор "123456789", CRC = 0xF4
TEST(CRC8Test, KnownString) {
    std::string str = "123456789";
    std::vector<uint8_t> data(str.begin(), str.end());
    EXPECT_EQ(crc8(data), 0xF4);
}

// CRC = 0x07 (проверка алгоритма)
TEST(CRC8Test, SingleByte) {
    std::vector<uint8_t> data = {0x01};
    EXPECT_EQ(crc8(data), 0x07);
}