#include "Vector.hpp"

#include <cmath>
#include <string>

namespace rt
{
namespace core
{

Vector Vector::crossProduct(const Vector& v)
{
    double x = y_ * v.z() - v.y() * z_; 
    double y = z_ * v.x() - v.z() * x_; 
    double z = x_ * v.y() - v.x() * y_;
    return Vector(x, y, z);
}

double Vector::dotProduct(const Vector& v)
{
    return (x()*v.x()) + (y()*v.y()) + (z()*v.z());
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

Vector Vector::operator+(const Point& p) const
{
    return Vector(x_ +p.x(), y_ + p.y(), z_ + p.z());
}

Vector Vector::operator*(const double& scale) const
{
    return Vector(x_ * scale, y_ * scale, z_ * scale);
}

double Vector::length() const
{
    return sqrt((x_ * x_) + (y_ * y_) + (z_ * z_));
}

}  // namespace core
}  // namespace rt