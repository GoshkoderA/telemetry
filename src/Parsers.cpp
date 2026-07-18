#include "Parsers.h"
#include <cstring> // для memcpy

static int16_t readInt16LE(const uint8_t* data) {
    return static_cast<int16_t>(data[0] | (data[1] << 8));
}

static uint16_t readUInt16LE(const uint8_t* data) {
    return static_cast<uint16_t>(data[0] | (data[1] << 8));
}

std::optional<ParsedData> TemperatureParser::parse(const std::vector<uint8_t>& payload) {
    if (payload.size() != 2) return std::nullopt;
    int16_t raw = readInt16LE(payload.data());
    return ParsedData{0x01, raw};
}

std::optional<ParsedData> FuelParser::parse(const std::vector<uint8_t>& payload) {
    if (payload.size() != 2) return std::nullopt;
    uint16_t value = readUInt16LE(payload.data());
    return ParsedData{0x02, value};
}

std::optional<ParsedData> DoorParser::parse(const std::vector<uint8_t>& payload) {
    if (payload.size() != 1) return std::nullopt;
    bool isOpen = (payload[0] != 0);
    return ParsedData{0x03, isOpen};
}

std::unique_ptr<IPayloadParser> ParserFactory::create(uint8_t type) {
    switch (type) {
        case 0x01: return std::make_unique<TemperatureParser>();
        case 0x02: return std::make_unique<FuelParser>();
        case 0x03: return std::make_unique<DoorParser>();
        default: return nullptr;
    }
}