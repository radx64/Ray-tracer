#include "Point.hpp"

namespace rt
{
namespace core
{

double Point::getX() const
{
    return x_;
}

double Point::getY() const
{
    return y_;
}

double Point::getZ() const
{
    return z_;
}

void Point::setX(double x)
{
    x_ = x;
}

void Point::setY(double y)
{
    y_ = y;
}

void Point::setZ(double z)
{
    z_ = z;
}

Point Point::operator + (const Point& p)
{
    return Point(getX()+p.getX(), getY()+p.getY(),getZ()+p.getZ());
}

Point Point::operator - (const Point& p)
{
    return Point(getX()-p.getX(), getY()-p.getY(),getZ()-p.getZ());
}

double Point::operator * (const Point& p)
{
    return getX()*p.getX() + getY()*p.getY() + getZ()*p.getZ();
}

std::ostream& operator<< (std::ostream& s, Point p)
{
    return s << "[" << p.getX() << ", " << p.getY() << ", " << p.getZ() << "]";
}

std::string Point::toString() const
{
    return std::string("["
        + std::to_string(x_) + ","
        + std::to_string(y_) + ","
        + std::to_string(z_) + "]");
}

}  // namespace core
}  // namespace rt 