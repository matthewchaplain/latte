#pragma once

#include "latte/log.h"

#include <functional>
#include <string>
#include <utility>
#include <cstdint>

template <typename RequestType>
class JournalLogger {
 public:
  JournalLogger(std::string base_name) : name_(std::move(base_name)) {}

  void LogRequest(
      std::int64_t sequence_number, const RequestType& request,
      const std::experimental::source_location& source = std::experimental::source_location::current()) const {
    LATTE_LOG_DEBUG("Request", {{"name", name_}, {"sequence number", sequence_number}, {"request", std::ref(request)}},
                    source);
  }

 private:
  std::string name_;
};
