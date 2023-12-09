#include "latte/print_json.h"

namespace latte {

void PrintJson(bool value) { std::cout << (value ? "True" : "False"); }

void PrintJson(float value) { std::cout << value; }

void PrintJson(double value) { std::cout << value; }

void PrintJson(std::int8_t value) { std::cout << value; }

void PrintJson(std::int16_t value) { std::cout << value; }

void PrintJson(std::int32_t value) { std::cout << value; }

void PrintJson(std::int64_t value) { std::cout << value; }

void PrintJson(std::uint8_t value) { std::cout << value; }

void PrintJson(std::uint16_t value) { std::cout << value; }

void PrintJson(std::uint32_t value) { std::cout << value; }

void PrintJson(std::uint64_t value) { std::cout << value; }

void PrintJson(std::string_view value) { std::cout << "\"" << value << "\""; }

}  // namespace latte