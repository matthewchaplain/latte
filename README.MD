# A front-end for a type-erased key-value pair logger

```cpp
#include "journal_logger.h"
#include "requester.h"
#include "latte/print_json.h"

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
```

```
<6>[2024-03-24 12:46:31] { "event": "Request", "name": "requester", "sequence number": 1, "request": {"varidx": 0, "value": 76}, file: "/workspaces/latte/journal_log/main.cc", line: 21 }
<6>[2024-03-24 12:46:31] { "event": "Request", "name": "requester", "sequence number": 2, "request": {"varidx": 1, "value": {"base": 34, "value": [1,2,3]}}, file: "/workspaces/latte/journal_log/main.cc", line: 22 }
```
