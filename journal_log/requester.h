#pragma once
#include <cstdint>
#include <experimental/source_location>

#include "null_logger.h"

template <typename RequestType, template <typename> typename Logger = NullLogger>
class Requester {
 public:
  void Request(const RequestType& value,
               const std::experimental::source_location& source = std::experimental::source_location::current()) {
    ++sequence_number_;
    logger_.LogRequest(sequence_number_, value, source);
    // Do actual request handling here...
  }

 private:
  Logger<RequestType> logger_{"requester"};
  std::uint32_t sequence_number_{0};
};