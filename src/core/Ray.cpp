#include "Ray.hpp"

namespace rt
{
namespace core
{

Point Ray::getOrgin()
{
    return orgin_;

}
void Ray::setOrgin(const Point& p)
{
    orgin_ = p;
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
    return std::string("ORGIN: ["
        + std::to_string(orgin_.getX()) + ","
        + std::to_string(orgin_.getY()) + ","
        + std::to_string(orgin_.getZ()) + "]"
        + "DIR: ["
        + std::to_string(direction_.getX()) + ","
        + std::to_string(direction_.getY()) + ","
        + std::to_string(direction_.getZ()) + "]"



        );
}

}  // namespace core
}  // namespace rt