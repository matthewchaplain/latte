#pragma once

#include <chrono>
#include <experimental/source_location>
#include <iomanip>
#include <iostream>
#include <string_view>

#include "latte/value.h"

namespace latte {

enum class LogLevel { Debug = 6 };

using KeyValue = std::pair<std::string_view, latte::Value>;
using KeyValueList = std::initializer_list<KeyValue>;

void LogEvent(std::string_view msg, LogLevel level, KeyValueList fields = {},
              const std::experimental::source_location& source = std::experimental::source_location::current()) {
  const auto now = std::chrono::system_clock::now();
  const auto now_in_time_t = std::chrono::system_clock::to_time_t(now);

  std::cout << "<" << static_cast<int>(level) << ">[" << std::put_time(std::localtime(&now_in_time_t), "%Y-%m-%d %X")
            << "] { \"event\": \"" << msg << "\"";
  for (const auto& key_value_pair : fields) {
    std::cout << ", \"" << key_value_pair.first << "\": ";
    key_value_pair.second.PrintJson();
  }
  std::cout << ", file: \"" << source.file_name() << "\", line: " << source.line() << " }\n";
}

}  // namespace latte

#define LATTE_LOG_DEBUG(msg, ...) latte::LogEvent(msg, latte::LogLevel::Debug __VA_OPT__(, ) __VA_ARGS__)
