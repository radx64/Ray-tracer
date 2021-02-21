#include "Point.hpp"

namespace rt::core
{

double Point::x() const
{
    return x_;
}

double Point::y() const
{
    return y_;
}

double Point::z() const
{
    return z_;
}

void Point::x(double x)
{
    x_ = x;
}

void Point::y(double y)
{
    y_ = y;
}

void Point::z(double z)
{
    z_ = z;
}

Point Point::operator + (const Point& p) const
{
    return Point(x()+p.x(), y()+p.y(),z()+p.z());
}

Point Point::operator - (const Point& p) const
{
    return Point(x()-p.x(), y()-p.y(),z()-p.z());
}

double Point::dot(const Point& p) const  /* dot product - must change to method to be similar to vector*/
{
    return x()*p.x() + y()*p.y() + z()*p.z();
}

std::ostream& operator<< (std::ostream& s, Point p)
{
    return s << p.toString();
}

Point Point::operator*(const double& scale) const
{
    return Point(x_ * scale, y_ * scale, z_ * scale);
}

std::string Point::toString() const
{
    return std::string("["
        + std::to_string(x_) + ", "
        + std::to_string(y_) + ", "
        + std::to_string(z_) + "]");
}

bool Point::operator== (const Point& p) const
{
    return ((x()==p.x()) and (y()==p.y()) and z()==p.z());
}

}  // namespace rt::core