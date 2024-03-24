#pragma once

#include "latte/value.h"

#include <experimental/source_location>
#include <string_view>

namespace latte {

enum class LogLevel { Debug = 6 };

using KeyValue = std::pair<std::string_view, latte::Value>;
using KeyValueList = std::initializer_list<KeyValue>;

void LogEvent(std::string_view msg, LogLevel level, KeyValueList fields = {},
              const std::experimental::source_location& source = std::experimental::source_location::current());

}  // namespace latte

#define LATTE_LOG_DEBUG(msg, ...) latte::LogEvent(msg, latte::LogLevel::Debug __VA_OPT__(, ) __VA_ARGS__)
