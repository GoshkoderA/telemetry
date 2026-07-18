#include "TelemetryStorage.h"

void TelemetryStorage::update(const ParsedData& data) {
    storage_[data.type] = data;
}

std::optional<ParsedData> TelemetryStorage::get(uint8_t type) const {
    auto it = storage_.find(type);
    if (it != storage_.end()) return it->second;
    return std::nullopt;
}