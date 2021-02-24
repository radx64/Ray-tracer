#include <gtest/gtest.h>

#include "core/Color.hpp"

namespace rt::testing {

TEST(ColorShould, increaseColorIntensity) {
  rt::core::Color c(10.0, 10.0, 10.0);
  rt::core::Color expected(30.0, 30.0, 30.0);

  EXPECT_EQ(c + 20.0, expected);
}

TEST(ColorShould, addTwoColors) {
  rt::core::Color c1(10.0, 10.0, 10.0);
  rt::core::Color c2(20.0, 30.0, 40.0);
  rt::core::Color expected(30.0, 40.0, 50.0);

  EXPECT_EQ(c1 + c2, expected);
}

TEST(ColorShould, decreaseColorIntensity) {
  rt::core::Color c(10.0, 10.0, 10.0);
  rt::core::Color expected(5.0, 5.0, 5.0);

  EXPECT_EQ(c - 5.0, expected);
}

TEST(ColorShould, subtractTwoColors) {
  rt::core::Color c1(10.0, 10.0, 10.0);
  rt::core::Color c2(5.0, 3.0, 1.0);
  rt::core::Color expected(5.0, 7.0, 9.0);

  EXPECT_EQ(c1 - c2, expected);
}

TEST(ColorShould, multiplyByColor) {
  rt::core::Color c1(10.0, 10.0, 10.0);
  rt::core::Color c2(5.0, 3.0, 1.0);
  rt::core::Color expected(50.0, 30.0, 10.0);

  EXPECT_EQ(c1 * c2, expected);
}

TEST(ColorShould, multiplyByFactor) {
  rt::core::Color c(10.0, 15.0, 20.0);
  rt::core::Color expected(30.0, 45.0, 60.0);

  EXPECT_EQ(c * 3.0, expected);
}

TEST(ColorShould, bePrintable) {
  rt::core::Color c(10.0, 15.0, 20.0);
  EXPECT_EQ(c.toString(), "[10.000000, 15.000000, 20.000000]");
}

} // namespace rt::testing
