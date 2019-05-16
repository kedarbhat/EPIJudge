#include <string>
#include "test_framework/generic_test.h"
using std::string;

bool IsPalindrome(const string& s) {
  auto fwdIter = std::cbegin(s);
  auto bwdIter = std::prev(std::cend(s));
  while (std::distance(fwdIter, bwdIter) > 0) {
    while (!std::isalnum(*fwdIter) && std::distance(fwdIter, bwdIter) > 0) {
      std::advance(fwdIter, 1);
    }

    while (!std::isalnum(*bwdIter) && std::distance(fwdIter, bwdIter) > 0) {
      std::advance(bwdIter, -1);
    }

    if (std::tolower(*fwdIter) != std::tolower(*bwdIter)) {
      return false;
    }
    std::advance(fwdIter, 1);
    std::advance(bwdIter, -1);
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
