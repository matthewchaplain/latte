#pragma once

#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string_view>
#include <variant>

#include "latte/overloaded.h"

namespace latte {

void PrintJson(bool value);
void PrintJson(float value);
void PrintJson(double value);
void PrintJson(std::int8_t value);
void PrintJson(std::int16_t value);
void PrintJson(std::int32_t value);
void PrintJson(std::int64_t value);
void PrintJson(std::uint8_t value);
void PrintJson(std::uint16_t value);
void PrintJson(std::uint32_t value);
void PrintJson(std::uint64_t value);
void PrintJson(std::string_view value);

template <typename T, std::size_t N>
void PrintJson(const std::array<T, N>& arr);

template <typename... KeyValuePairs>
void PrintJsonObject(KeyValuePairs&&... key_value_pairs);

namespace detail {
template <typename... KeyValuePairs>
void PrintJsonObjectKeyValuePairs(std::size_t index, std::string_view next_key,
                                  const KeyValuePairs&... key_value_pairs);

inline void PrintJsonObjectKeyValuePairs(std::size_t) {}

template <typename Value, typename... KeyValuePairs>
void PrintJsonObjectKeyValuePairs(std::size_t index, std::string_view key, const Value& value,
                                  const KeyValuePairs&... key_value_pairs) {
  using latte::PrintJson;

  if (index) {
    std::cout << ", ";
  }

  std::cout << "\"" << key << "\": ";
  PrintJson(value);
  PrintJsonObjectKeyValuePairs(index + 1, key_value_pairs...);
}

}  // namespace detail

template <typename... KeyValuePairs>
void PrintJsonObject(const KeyValuePairs&... key_value_pairs) {
  std::cout << "{";
  detail::PrintJsonObjectKeyValuePairs(0U, key_value_pairs...);
  std::cout << "}";
}

template <typename Range>
void PrintJsonArray(const Range& range) {
  std::cout << "[";

  auto current = std::cbegin(range);
  const auto end = std::cend(range);

  if (current != end) {
    PrintJson(*current);
    ++current;
  }

  for (; current != end; ++current) {
    std::cout << ",";
    PrintJson(*current);
  }
}

template <typename T, std::size_t N>
void PrintJson(const std::array<T, N>& arr) {
  PrintJsonArray(arr);
}

template <typename... Ts>
void PrintJson(const std::variant<Ts...>& value) {
  std::visit(latte::overloaded{[index = value.index()](const auto& inner_value) {
               PrintJsonObject("varidx", index, "value", inner_value);
             }},
             value);
}

template <typename T>
void PrintJson(std::reference_wrapper<T> value) {
  using latte::PrintJson;
  PrintJson(value.get());
}

}  // namespace latte