#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <utility>

#include "latte/log.h"

template <typename RequestType>
class JournalLogger {
 public:
  JournalLogger(std::string base_name) : name_(std::move(base_name)) {}

  void LogRequest(std::int64_t sequence_number, const RequestType& request) const {
    LATTE_LOG_DEBUG("Request", {{"name", name_}, {"sequence number", sequence_number}, {"request", std::ref(request)}});
  }

 private:
  std::string name_;
};
