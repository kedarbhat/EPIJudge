#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  if (A.empty()) {
    return std::vector<int>{1};
  }

  bool carry = false;
  for (auto iter = std::rbegin(A); iter != std::rend(A);) {
    carry = *iter == 9;
    if (carry) {
      *iter = 0;
      std::advance(iter, 1);
    } else {
      ++(*iter);
      iter = std::rend(A);
    }
  }
  if (carry) {
    A.insert(std::begin(A), 1);
  }
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
