#ifndef RT_CORE_VECTOR_HPP_
#define RT_CORE_VECTOR_HPP_

#include "Point.hpp"

namespace rt::core
{

class Vector : public Point
{
public:
    Vector(double x, double y, double z);
    Vector();
    Vector(const Point& p);
    Vector(const Vector& v);

    Vector& operator=(const Vector& v) = default;

    Vector cross(const Vector& v);
    double length() const;
    bool isZero() const;
    void normalize();
};

}  // namespace rt::core

#endif  // RT_CORE_VECTOR_HPP_