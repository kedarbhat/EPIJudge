#include <algorithm>
#include <vector>

#include "test_framework/generic_test.h"

std::vector<int> KLargestInBinaryHeap(const std::vector<int>& A, int k) {
  if (k <= 0) {
    return std::vector<int>{};
  }
  std::vector<int> result;
  result.reserve(k);
  std::priority_queue<std::pair<int, std::size_t>> heap;
  heap.emplace(std::make_pair(A.front(), 0));
  for (auto idx = 0u; idx < k; ++idx) {
    std::ignore = idx;
    auto top_idx = heap.top().second;
    result.emplace_back(heap.top().first);
    heap.pop();

    auto left_child_idx = 2 * top_idx + 1;
    if (left_child_idx < A.size()) {
      heap.emplace(std::make_pair(A[left_child_idx], left_child_idx));
    }

    auto right_child_idx = 2 * top_idx + 2;
    if (right_child_idx < A.size()) {
      heap.emplace(std::make_pair(A[right_child_idx], right_child_idx));
    }
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "k_largest_in_heap.cc", "k_largest_in_heap.tsv",
                         &KLargestInBinaryHeap,
                         &UnorderedComparator<std::vector<int>>, param_names);
}
