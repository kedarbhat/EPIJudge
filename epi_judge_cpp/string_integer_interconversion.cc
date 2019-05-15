#include <string>
#include <sstream>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  auto isNegative = std::signbit(x);

  std::stringstream ss;
  do {
    auto c = char('0' + std::abs(x % 10));
    ss << c;
    x /= 10;
  } while (x != 0);
  if (isNegative) {
    ss << '-';
  }
  auto str = ss.str();
  return {std::crbegin(str), std::crend(str)};
}

int StringToInt(const string& s) {
  int result = 0;
  int multiplier = 1;
  for (auto c : s) {
    assert(std::isdigit(c) || c == '-');
    if (c == '-') {
      multiplier *= -1;
    } else {
      result *= 10;
      result += (c - '0');
    }
  }
  return multiplier * result;
}

void Wrapper(int x, const string& s) {
  if (IntToString(x) != s) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
