#include "shape/Light.hpp"

namespace rt
{
namespace shape
{

Light::Light() : logger_("Light")
{

}

void Light::setColor(core::Color color)
{
    color_ = color;
}
core::Color Light::getColor()
{
    return color_;
}

core::Vector Light::getNormalAt([[maybe_unused]] core::Point& p)
{
	return core::Vector(0.0,0.0,0.0);
}

bool Light::hit([[maybe_unused]] core::Ray r, [[maybe_unused]] double& dist)
{
	return false;
}

core::Vector Light::UV([[maybe_unused]] const core::Point& p)
{
    return core::Vector{0.0, 0.0, 0.0};
}

const core::Material& Light::getMaterialAt([[maybe_unused]] const core::Point& p)
{
    return getMaterial();
}

}  // namespace shape
}  // namespace rt