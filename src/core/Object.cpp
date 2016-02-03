#include "Object.hpp"

namespace rt
{
namespace core
{

void Object::setMaterial(Material material)
{
    material_ = material;
}

core::Material Object::getMaterial()
{
    return material_;
}

void Object::setPosition(Point& p)
{
    position_ = p;
}

Point Object::getPosition()
{
    return position_;
}

}  // namespace core
}  // namespace return