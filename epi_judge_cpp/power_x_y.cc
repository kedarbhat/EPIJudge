#include "test_framework/generic_test.h"
double Power(double x, int y) {
  if (std::fpclassify(x) == FP_ZERO) {
    return 0;
  }

  auto power = int64_t(y);
  auto result = 1.0;
  if (power < 0) {
    power *= -1;
    x = 1/x;
  }
  while (power > 0) {
    if (power % 2 != 0) {
      result *= x;
    }
    x *= x;
    power /= 2;
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}
