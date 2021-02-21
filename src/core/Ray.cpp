#include "Ray.hpp"

namespace rt::core
{

Ray::Ray(const Point& o, const Vector& dir)
: origin_(o), direction_(dir)
{

}

Point Ray::getOrigin()
{
    return origin_;

}
void Ray::setOrigin(const Point& p)
{
    origin_ = p;
}
Vector Ray::getDirection()
{
    return direction_;
}
void Ray::setDirection(const Vector& v)
{
    direction_ = v;
}
std::string Ray::toString() const
{
    return std::string("ORIGIN: ["
        + std::to_string(origin_.x()) + ", "
        + std::to_string(origin_.y()) + ", "
        + std::to_string(origin_.z()) + "]"
        + " DIR: ["
        + std::to_string(direction_.x()) + ", "
        + std::to_string(direction_.y()) + ", "
        + std::to_string(direction_.z()) + "]"
        );
}

}  // namespace rt::core