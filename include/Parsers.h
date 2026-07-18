#pragma once
#include "IPayloadParser.h"
#include <memory>

class TemperatureParser : public IPayloadParser {
public:
    std::optional<ParsedData> parse(const std::vector<uint8_t>& payload) override;
};

class FuelParser : public IPayloadParser {
public:
    std::optional<ParsedData> parse(const std::vector<uint8_t>& payload) override;
};

class DoorParser : public IPayloadParser {
public:
    std::optional<ParsedData> parse(const std::vector<uint8_t>& payload) override;
};

class ParserFactory {
public:
    static std::unique_ptr<IPayloadParser> create(uint8_t type);
};