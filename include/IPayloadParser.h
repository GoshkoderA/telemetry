#pragma once
#include <cstdint>
#include <vector>
#include <variant>
#include <optional>

using PayloadValue = std::variant<int16_t, uint16_t, bool>;

struct ParsedData {
    uint8_t type;
    PayloadValue value;
};

class IPayloadParser {
public:
    virtual ~IPayloadParser() = default;
    virtual std::optional<ParsedData> parse(const std::vector<uint8_t>& payload) = 0;
};