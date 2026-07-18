#include "TelemetryProcessor.h"
#include "Parsers.h"

TelemetryProcessor::TelemetryProcessor(TelemetryStorage& storage)
    : storage_(storage) {}

void TelemetryProcessor::handleFrame(uint8_t type, const std::vector<uint8_t>& payload) {
    auto parser = ParserFactory::create(type);
    if (!parser) return; // неизвестный тип
    auto parsed = parser->parse(payload);
    if (parsed) {
        storage_.update(*parsed);
    }
}

std::optional<ParsedData> TelemetryProcessor::getValue(uint8_t type) const {
    return storage_.get(type);
}