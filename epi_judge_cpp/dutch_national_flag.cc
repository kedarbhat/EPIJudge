#include <array>
#include <cassert>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

using Color = enum { kRed, kWhite, kBlue };

void DutchFlagPartition(int pivot_index, std::vector<Color>* A_ptr) {
  if (A_ptr == nullptr) {
    return;
  }

  using diff_t = typename std::vector<Color>::difference_type;
  auto& A = *A_ptr;
  auto pivot_element =  A[pivot_index];
  auto low_idx = std::size_t{0};
  auto mid_idx = std::size_t{0};
  auto high_idx = A.size();

  while (mid_idx < high_idx) {
    if (A[mid_idx] < pivot_element) {
      std::swap(A[mid_idx], A[low_idx]);
      ++low_idx;
      ++mid_idx;
    } else if (A[mid_idx] > pivot_element) {
      std::swap(A[mid_idx], A[high_idx - 1]);
      --high_idx;
    } else {
      ++mid_idx;
    }
    assert(std::all_of(std::cbegin(A), std::cbegin(A)+diff_t(low_idx), [pivot_element](auto&& i) { return i < pivot_element; }));
    assert(std::all_of(std::cbegin(A)+diff_t(low_idx), std::cbegin(A)+diff_t(mid_idx), [pivot_element](auto&& i) { return i == pivot_element; }));
    assert(std::all_of(std::cbegin(A)+diff_t(high_idx), std::cend(A), [pivot_element](auto&& i) { return i > pivot_element; }));
  }
}
void DutchFlagPartitionWrapper(TimedExecutor& executor, const std::vector<int>& A,
                               int pivot_idx) {
  std::vector<Color> colors;
  colors.resize(A.size());
  std::array<int, 3> count = {0, 0, 0};
  for (size_t i = 0; i < A.size(); i++) {
    count[A[i]]++;
    colors[i] = static_cast<Color>(A[i]);
  }
  Color pivot = colors[pivot_idx];

  executor.Run([&] { DutchFlagPartition(pivot_idx, &colors); });

  int i = 0;
  while (i < colors.size() && colors[i] < pivot) {
    count[colors[i]]--;
    ++i;
  }

  while (i < colors.size() && colors[i] == pivot) {
    count[colors[i]]--;
    ++i;
  }

  while (i < colors.size() && colors[i] > pivot) {
    count[colors[i]]--;
    ++i;
  }

  if (i != colors.size()) {
    throw TestFailure("Not partitioned after " + std::to_string(i) +
                      "th element");
  } else if (count != std::array<int, 3>{0, 0, 0}) {
    throw TestFailure("Some elements are missing from original array");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A", "pivot_idx"};
  return GenericTestMain(args, "dutch_national_flag.cc",
                         "dutch_national_flag.tsv", &DutchFlagPartitionWrapper,
                         DefaultComparator{}, param_names);
}
