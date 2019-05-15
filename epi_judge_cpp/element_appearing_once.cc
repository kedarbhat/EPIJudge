#include <vector>
#include <climits>
#include "test_framework/generic_test.h"

int FindElementAppearsOnce(const std::vector<int>& A) {
  std::array<int, sizeof(int)*CHAR_BIT> elementCounts{};
  for (auto x : A) {
    for (auto & elementCount : elementCounts) {
      elementCount += x & 1;
      x >>= 1;
    }
  }

  auto result = 0;
  for (int i = 0; i < elementCounts.size(); ++i) {
    result |= elementCounts[i] % 3 << i;
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "element_appearing_once.cc",
                         "element_appearing_once.tsv", &FindElementAppearsOnce,
                         DefaultComparator{}, param_names);
}
