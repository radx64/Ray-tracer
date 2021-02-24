#include <gtest/gtest.h>

#include "core/Point.hpp"

namespace rt::testing {

TEST(PointShould, getProperCoordinates) {
  rt::core::Point p(0.0, 10.0, 20.0);

  EXPECT_DOUBLE_EQ(p.x(), 0.0);
  EXPECT_DOUBLE_EQ(p.y(), 10.0);
  EXPECT_DOUBLE_EQ(p.z(), 20.0);
}

TEST(PointShould, setCoordinatesProperly) {
  rt::core::Point p(100.0, 100.0, 100.0);
  p.x(0.0);
  p.y(10.0);
  p.z(20.0);
  EXPECT_DOUBLE_EQ(p.x(), 0.0);
  EXPECT_DOUBLE_EQ(p.y(), 10.0);
  EXPECT_DOUBLE_EQ(p.z(), 20.0);
}

TEST(PointShould, addPoints) {
  rt::core::Point p1(100.0, 100.0, 100.0);
  rt::core::Point p2(200.0, 300.0, 400.0);

  rt::core::Point expected_result(300.0, 400.0, 500.0);
  rt::core::Point result = p1 + p2;

  EXPECT_EQ(result, expected_result);
}

TEST(PointShould, subtractPoints) {
  rt::core::Point p1(100.0, 100.0, 100.0);
  rt::core::Point p2(200.0, 300.0, 400.0);

  rt::core::Point expected_result(-100.0, -200.0, -300.0);
  rt::core::Point result = p1 - p2;

  EXPECT_EQ(result, expected_result);
}

TEST(PointShould, calculateDotProduct) {
  double x1, y1, z1;
  double x2, y2, z2;
  x1 = y1 = z1 = 100.0;
  x2 = y2 = z2 = 200.0;

  rt::core::Point p1(x1, y1, z1);
  rt::core::Point p2(x2, y2, z2);

  double expected_dot_product_result = x1 * x2 + y1 * y2 + z1 * z2;

  EXPECT_DOUBLE_EQ(p1.dot(p2), expected_dot_product_result);
}

TEST(PointShould, beScalableByAFactor) {
  rt::core::Point p(100.0, 100.0, 100.0);
  rt::core::Point expected_result(300.0, 300.0, 300.0);

  rt::core::Point result = p * 3.0;
  EXPECT_EQ(result, expected_result);
}

TEST(PointShould, bePrintable) {
  rt::core::Point p(100.0, 100.0, 100.0);

  EXPECT_EQ(p.toString(), "[100.000000, 100.000000, 100.000000]");
}

} // namespace rt::testing