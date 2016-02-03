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

core::Vector Light::getNormalAt(core::Point& p)
{
	return core::Vector(0.0,0.0,0.0);
}

bool Light::hit(core::Ray r, double& dist)
{
	return false;
}


}  // namespace shape
}  // namespace rt