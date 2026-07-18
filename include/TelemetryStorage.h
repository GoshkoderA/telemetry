#pragma once
#include "IPayloadParser.h"
#include <unordered_map>
#include <optional>

class TelemetryStorage {
public:
    void update(const ParsedData& data);
    std::optional<ParsedData> get(uint8_t type) const;
private:
    std::unordered_map<uint8_t, ParsedData> storage_;
};