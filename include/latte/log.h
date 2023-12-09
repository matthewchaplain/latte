#pragma once

#include <any>
#include <experimental/source_location>
#include <string_view>

namespace latte {

enum class LogLevel { Debug };

using KeyValue = std::pair<std::string_view, std::any>;
using KeyValueList = std::initializer_list<KeyValue>;

void LogEvent(const std::experimental::source_location& source, std::string_view msg, LogLevel, KeyValueList fields) {}

}  // namespace latte

#define LATTE_LOG_(msg, type, ...)                                 \
  [&, source = std::experimental::source_location::current()] {    \
    latte::LogEvent(source, msg, type __VA_OPT__(, ) __VA_ARGS__); \
  }();
#define LATTE_LOG_DEBUG(msg, ...) LATTE_LOG_(msg, latte::LogLevel::Debug __VA_OPT__(, ) __VA_ARGS__)
