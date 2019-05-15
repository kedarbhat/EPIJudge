#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  if (A.empty()) {
    return std::vector<int>{1};
  }

  int carry = 0;
  for (auto iter = std::rbegin(A); iter != std::rend(A); iter = carry == 1 ? std::next(iter, 1) : std::rend(A)) {
    if (*iter == 9) {
      *iter = 0;
      carry = 1;
    } else {
      ++(*iter);
      carry = 0;
    }
  }
  if (carry == 1) {
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
