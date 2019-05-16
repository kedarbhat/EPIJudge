#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;

void ReverseWords(string* s_ptr) {
  if (s_ptr == nullptr) {
    return;
  }

  auto& s = *s_ptr;

  std::reverse(std::begin(s), std::end(s));
  auto spaceIdx = s.find(' ', 0);
  auto lastStartOfWordIdx = 0;

  while (spaceIdx != std::string::npos) {
    assert(s[spaceIdx] == ' ');
    std::reverse(std::begin(s)+lastStartOfWordIdx, std::begin(s)+spaceIdx);
    lastStartOfWordIdx = spaceIdx+1;
    spaceIdx = s.find(' ', lastStartOfWordIdx);
  }
  std::reverse(std::begin(s)+lastStartOfWordIdx, std::end(s));
}

string ReverseWordsWrapper(TimedExecutor& executor, string s) {
  string s_copy = s;

  executor.Run([&] { ReverseWords(&s_copy); });

  return s_copy;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "s"};
  return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
                         &ReverseWordsWrapper, DefaultComparator{},
                         param_names);
}
