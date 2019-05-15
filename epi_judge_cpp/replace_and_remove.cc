#include <iterator>
#include <string>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

int ReplaceAndRemove(int size, char s[]) {
  if (size == 0) {
    return 0;
  }

  auto a_counter = 0;
  auto write_idx = 0;
  for (auto read_idx = 0; read_idx < size; ++read_idx) {
    if (s[read_idx] != 'b') { // delete b's
      s[write_idx] = s[read_idx];
      ++write_idx;
      if (s[read_idx] == 'a') {
        ++a_counter;
      }
    }
  }

  auto read_idx = write_idx-1;
  write_idx = write_idx + a_counter - 1;
  auto new_size = write_idx + 1;
  for (; read_idx >= 0; --read_idx) {
    if (s[read_idx] == 'a') {
      s[write_idx--] = 'd';
      s[write_idx--] = 'd';
    } else {
      s[write_idx--] = s[read_idx];
    }
  }

  return new_size;
}

vector<string> ReplaceAndRemoveWrapper(TimedExecutor& executor, int size,
                                       const vector<string>& s) {
  std::vector<char> s_copy(s.size(), '\0');
  for (int i = 0; i < s.size(); ++i) {
    if (!s[i].empty()) {
      s_copy[i] = s[i][0];
    }
  }

  int res_size =
      executor.Run([&] { return ReplaceAndRemove(size, s_copy.data()); });

  vector<string> result;
  for (int i = 0; i < res_size; ++i) {
    result.emplace_back(string(1, s_copy[i]));
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "size", "s"};
  return GenericTestMain(args, "replace_and_remove.cc",
                         "replace_and_remove.tsv", &ReplaceAndRemoveWrapper,
                         DefaultComparator{}, param_names);
}
