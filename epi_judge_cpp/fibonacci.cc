#include "test_framework/generic_test.h"
int Fibonacci(int n) {
  if (n < 2) {
    return n;
  }
  auto prev_1 = 1;
  auto prev_2 = 0;
  for (auto i = 2; i <= n; ++i) {
    auto current = prev_1 + prev_2;
    prev_2 = prev_1;
    prev_1 = current;
  }
  return prev_1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "fibonacci.cc", "fibonacci.tsv", &Fibonacci,
                         DefaultComparator{}, param_names);
}
