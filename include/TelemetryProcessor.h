#pragma once
#include "TelemetryStorage.h"
#include <vector>
#include <cstdint>
#include <optional>

class TelemetryProcessor {
public:
    explicit TelemetryProcessor(TelemetryStorage& storage);
    void handleFrame(uint8_t type, const std::vector<uint8_t>& payload);
    std::optional<ParsedData> getValue(uint8_t type) const;
private:
    TelemetryStorage& storage_;
};