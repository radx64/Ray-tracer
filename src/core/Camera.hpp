#ifndef RT_CORE_CAMERA_HPP_
#define RT_CORE_CAMERA_HPP_

#include "Point.hpp"
#include "Vector.hpp"

namespace rt::core
{

struct Camera
{
    Point position_;
    Vector rotation_;
    Vector fov_; // should use something like Vec2 for that but I'm lazy
};

}  // namespace rt::core

#endif  // CORE_CAMERA_HPP