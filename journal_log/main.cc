#include "journal_logger.h"
#include "latte/print_json.h"
#include "requester.h"

#include <array>

namespace test {

struct MyTest {
  int base;
  std::array<int, 3> value;
};

void PrintJson(const MyTest& my_test);

}  // namespace test

int main() {
  using Type = std::variant<int, test::MyTest>;
  Requester<Type, JournalLogger> requester;
  requester.Request(76);
  requester.Request(test::MyTest{34, {1, 2, 3}});
}

namespace test {
void PrintJson(const MyTest& my_test) { latte::PrintJsonObject("base", my_test.base, "value", my_test.value); }
}  // namespace test
