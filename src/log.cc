#include "latte/log.h"

#include <chrono>
#include <iomanip>
#include <iostream>

namespace latte {

void LogEvent(std::string_view msg, LogLevel level, KeyValueList fields /* = {} */,
              const std::experimental::source_location& source /* = std::experimental::source_location::current() */) {
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