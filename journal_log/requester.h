#pragma once
#include <cstdint>

#include "null_logger.h"

template <typename T, template <typename> typename Logger = NullLogger>
class Requester {
 public:
  void Request(const T& value,
               const std::experimental::source_location& source = std::experimental::source_location::current()) {
    ++sequence_number_;
    logger_.LogRequest(sequence_number_, value, source);
    // Do actual request handling here...
  }

 private:
  Logger<T> logger_{"requester"};
  std::uint32_t sequence_number_{0};
};