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
};

}  // namespace rt::core

#endif  // CORE_CAMERA_HPP