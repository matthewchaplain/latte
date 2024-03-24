#pragma once

#include <experimental/source_location>
#include <string>

template <typename RequestType>
class NullLogger {
 public:
  NullLogger(std::string) {}

  void LogRequest(
      std::int64_t /* sequence_number */, const RequestType& /* request */,
      const std::experimental::source_location& /* source */ = std::experimental::source_location::current()) const {}
};
