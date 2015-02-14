#include "Object.hpp"

namespace rt
{
namespace core
{

void Object::setPosition(Point& p)
{
    position_ = p;
}

Point Object::getPosition()
{
    return position_;
}

void Object::setType(Object::Type type)
{
    type_ = type;
}

Object::Type Object::getType()
{
    return type_;
}

}  // namespace core
}  // namespace return