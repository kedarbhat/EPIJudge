#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::vector;

void RotateArray(int rotate_amount, vector<int>* A_ptr) {
  if (A_ptr == nullptr) {
    return;
  }
  auto& A = *A_ptr;
  rotate_amount %= A.size();

  std::reverse(std::rbegin(A), std::rbegin(A) + rotate_amount);
  std::reverse(std::rbegin(A) + rotate_amount, std::rend(A));
  std::reverse(std::rbegin(A), std::rend(A));
}

vector<int> RotateArrayWrapper(TimedExecutor& executor, vector<int> A,
                               int rotate_amount) {
  executor.Run([&] { RotateArray(rotate_amount, &A); });
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A", "rotate_amount"};
  return GenericTestMain(args, "rotate_array.cc", "rotate_array.tsv",
                         &RotateArrayWrapper, DefaultComparator{}, param_names);
}
