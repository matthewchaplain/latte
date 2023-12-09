#pragma once
#include <cstdint>

template <typename T, template <typename> typename Logger>
class Requester {
 public:
  void Request(const T& value) {
    ++sequence_number_;
    logger_.LogRequest(sequence_number_, value);
    // Do actual request handling here...
  }

 private:
  Logger<T> logger_{"requester"};
  std::uint32_t sequence_number_{0};
};