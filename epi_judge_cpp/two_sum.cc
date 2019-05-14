#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

bool HasTwoSum(const vector<int>& A, int t) {
  assert(std::is_sorted(std::cbegin(A), std::cend(A)));

  if (A.empty()) {
    return false;
  }

  auto fwd_iter = std::cbegin(A);
  auto bwd_iter = std::prev(std::cend(A));
  while (std::distance(fwd_iter, bwd_iter) >= 0) {
    auto current = *fwd_iter + *bwd_iter;
    if (current > t) {
      std::advance(bwd_iter, -1);
    } else if (current < t) {
      std::advance(fwd_iter, 1);
    } else {
      return true;
    }
  }
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "two_sum.cc", "two_sum.tsv", &HasTwoSum,
                         DefaultComparator{}, param_names);
}
