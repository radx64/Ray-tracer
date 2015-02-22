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


}  // namespace core
}  // namespace rt