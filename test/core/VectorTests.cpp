#include <gtest/gtest.h>

#include "core/Vector.hpp"

namespace rt::testing {
TEST(VectorShould, getProperCoordinates) {
  rt::core::Vector v(0.0, 10.0, 20.0);

  EXPECT_DOUBLE_EQ(v.x(), 0.0);
  EXPECT_DOUBLE_EQ(v.y(), 10.0);
  EXPECT_DOUBLE_EQ(v.z(), 20.0);
}

TEST(VectorShould, setCoordinatesProperly) {
  rt::core::Vector v(100.0, 100.0, 100.0);
  v.x(0.0);
  v.y(10.0);
  v.z(20.0);
  EXPECT_DOUBLE_EQ(v.x(), 0.0);
  EXPECT_DOUBLE_EQ(v.y(), 10.0);
  EXPECT_DOUBLE_EQ(v.z(), 20.0);
}

TEST(VectorShould, addVectors) {
  rt::core::Vector v1(100.0, 100.0, 100.0);
  rt::core::Vector v2(200.0, 300.0, 400.0);

  rt::core::Vector expected_result(300.0, 400.0, 500.0);
  rt::core::Vector result = v1 + v2;

  EXPECT_EQ(result, expected_result);
}

TEST(VectorShould, subtractVectors) {
  rt::core::Vector v1(100.0, 100.0, 100.0);
  rt::core::Vector v2(200.0, 300.0, 400.0);

  rt::core::Vector expected_result(-100.0, -200.0, -300.0);
  rt::core::Vector result = v1 - v2;

  EXPECT_EQ(result, expected_result);
}

TEST(VectorShould, calculateDotProduct) {
  double x1, y1, z1;
  double x2, y2, z2;
  x1 = y1 = z1 = 100.0;
  x2 = y2 = z2 = 200.0;

  rt::core::Vector v1(x1, y1, z1);
  rt::core::Vector v2(x2, y2, z2);

  double expected_dot_product_result = x1 * x2 + y1 * y2 + z1 * z2;

  EXPECT_DOUBLE_EQ(v1.dot(v2), expected_dot_product_result);
}

TEST(VectorShould, beScalableByAFactor) {
  rt::core::Vector v(100.0, 100.0, 100.0);
  rt::core::Vector expected_result(300.0, 300.0, 300.0);

  rt::core::Vector result = v * 3.0;
  EXPECT_EQ(result, expected_result);
}

TEST(VectorShould, bePrintable) {
  rt::core::Vector v(100.0, 100.0, 100.0);

  EXPECT_EQ(v.toString(), "[100.000000, 100.000000, 100.000000]");
}

TEST(VectorShould, calculateCorrectCrossProduct) {
  rt::core::Vector v1(10.0, 20.0, 30.0);
  rt::core::Vector v2(30.0, 40.0, 50.0);

  rt::core::Vector expected_result(-200.0, 400.0, -200.0);

  EXPECT_EQ(v1.cross(v2), expected_result);
}

TEST(VectorShould, calculateLength) {
  rt::core::Vector v(10.0, 20.0, 30.0);
  double expected_length = 37.4166;
  EXPECT_NEAR(v.length(), expected_length, 0.0001);

  v = rt::core::Vector(15.0, 27.0, 33.0);
  expected_length = 45.1995;
  EXPECT_NEAR(v.length(), expected_length, 0.0001);
}

TEST(VectorShould, returnIfIsZeroLength) {
  rt::core::Vector v(10.0, 20.0, 30.0);
  EXPECT_FALSE(v.isZero());

  v = rt::core::Vector(0.0, 0.0, 0.0);
  EXPECT_TRUE(v.isZero());
}

TEST(VectorShould, normalizeItself) {
  rt::core::Vector v(10.0, 20.0, 30.0);
  rt::core::Vector expected_normalized_vector(0.267261, 0.534522, 0.801784);
  v.normalize();
  EXPECT_NEAR(v.x(), expected_normalized_vector.x(), 0.0001);
  EXPECT_NEAR(v.y(), expected_normalized_vector.y(), 0.0001);
  EXPECT_NEAR(v.z(), expected_normalized_vector.z(), 0.0001);

  v = rt::core::Vector(95.0, 43.0, 11.0);
  expected_normalized_vector = rt::core::Vector(0.905995, 0.410082, 0.104905);
  v.normalize();
  EXPECT_NEAR(v.x(), expected_normalized_vector.x(), 0.0001);
  EXPECT_NEAR(v.y(), expected_normalized_vector.y(), 0.0001);
  EXPECT_NEAR(v.z(), expected_normalized_vector.z(), 0.0001);
}

} // namespace rt::testing