#ifndef RT_CORE_VECTOR_HPP_
#define RT_CORE_VECTOR_HPP_

#include "Point.hpp"

namespace rt
{
namespace core
{

class Vector : public Point
{
public:
    Vector(double x, double y, double z) : Point(x, y, z)
    { };
    Vector() : Point(0.0, 0.0, 0.0)
    { };
    Vector(const Point& p) : Point(p)
    { };
    Vector(const Vector& v) : Point(v.x_,v.y_,v.z_)
    { };

    Vector& operator=(const Vector& v) = default;

    Vector crossProduct(const Vector& v);
    double dotProduct(const Vector& v);
    double length() const;
    bool isZero() const;
    void normalize();

    Vector operator+(const Point& p) const;
    Vector operator*(const double& scale) const;
};

}  // namespace core
}  // namespace rt

#endif  // RT_CORE_VECTOR_HPP_