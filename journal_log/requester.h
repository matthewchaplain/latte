#pragma once
#include "null_logger.h"

#include <experimental/source_location>
#include <cstdint>

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