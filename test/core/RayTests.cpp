#include <gtest/gtest.h>

#include "core/Ray.hpp"

namespace rt::testing {

TEST(RayShould, getProperOriginPoint) {
  rt::core::Point origin(0.0, 10.0, 20.0);
  rt::core::Vector direction(10.0, 20.0, 30.0);

  rt::core::Ray ray(origin, direction);

  EXPECT_EQ(ray.getOrigin(), origin);
}

TEST(RayShould, getProperDirectionVector) {
  rt::core::Point origin(0.0, 10.0, 20.0);
  rt::core::Vector direction(10.0, 20.0, 30.0);

  rt::core::Ray ray(origin, direction);

  EXPECT_EQ(ray.getDirection(), direction);
}

TEST(RayShould, setNewOriginPoint) {
  rt::core::Point origin(0.0, 10.0, 20.0);
  rt::core::Vector direction(10.0, 20.0, 30.0);

  rt::core::Ray ray(origin, direction);
  rt::core::Point new_origin(100.0, 200.0, 300.0);
  ray.setOrigin(new_origin);

  EXPECT_EQ(ray.getOrigin(), new_origin);
}

TEST(RayShould, setNewDirectionVector) {
  rt::core::Point origin(0.0, 10.0, 20.0);
  rt::core::Vector direction(10.0, 20.0, 30.0);

  rt::core::Ray ray(origin, direction);
  rt::core::Vector new_direction(10.0, 20.0, 30.0);
  ray.setDirection(new_direction);

  EXPECT_EQ(ray.getDirection(), new_direction);
}

TEST(RayShould, bePrintable) {
  rt::core::Point origin(0.0, 10.0, 20.0);
  rt::core::Vector direction(10.0, 20.0, 30.0);

  rt::core::Ray ray(origin, direction);
  EXPECT_EQ(ray.toString(), "ORIGIN: [0.000000, 10.000000, 20.000000] DIR: "
                            "[10.000000, 20.000000, 30.000000]");
}

} // namespace rt::testing