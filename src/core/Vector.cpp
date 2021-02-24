#include "Vector.hpp"

#include <cmath>
#include <string>

namespace rt::core
{

Vector::Vector(double x, double y, double z) : Point(x, y, z)
{ };

Vector::Vector() : Point(0.0, 0.0, 0.0)
{ };

Vector::Vector(const Point& p) : Point(p)
{ };

Vector::Vector(const Vector& v) : Point(v.x_,v.y_,v.z_)
{ };


Vector Vector::cross(const Vector& v)
{
    double x = y_ * v.z() - v.y() * z_; 
    double y = z_ * v.x() - v.z() * x_; 
    double z = x_ * v.y() - v.x() * y_;
    return Vector(x, y, z);
}

void Vector::normalize()
{
    double length = Vector::length();
    x_ /= length;
    y_ /= length;
    z_ /= length;
}

bool Vector::isZero() const
{
    return ((0 == x_) && (0 == y_) && (0 == z_));
}

double Vector::length() const
{
    return sqrt((x_ * x_) + (y_ * y_) + (z_ * z_));
}

}  // namespace rt::core