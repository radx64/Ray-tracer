#include "Object.hpp"

namespace rt
{
namespace core
{

void Object::setMaterial(Material material)
{
    material_ = material;
}

const core::Material& Object::getMaterial()
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

const core::Material& Object::getMaterialAt(const Point& p)
{
    return material_;    
}

const core::Vector Object::UV(const Point& p)
{
    return core::Vector{0.0, 0.0, 0.0};
}

}  // namespace core
}  // namespace return