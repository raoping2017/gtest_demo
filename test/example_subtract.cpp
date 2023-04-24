#include <gtest/gtest.h>

#include "example.h"

TEST(example, subtract) {
  double res;
  res = subtract_numbers(1.0, 2.0);
  std::set<int> a1;
  a1.insert(1);
  a1.insert(2);
  a1.insert(3);
  ASSERT_NEAR(res, -1.0, 1.0e-11);
}
