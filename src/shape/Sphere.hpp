#ifndef RT_SHAPE_SPHERE_HPP_
#define RT_SHAPE_SPHERE_HPP_

#include <memory>

#include "core/Object.hpp"
#include "core/Vector.hpp"

namespace rt
{
namespace shape
{

class Sphere : public core::Object
{
public:
    Sphere()
    { }

    virtual core::Vector getNormalAt(core::Point& p);
    virtual bool Hit(core::Ray r, double& dist);

    void setRadius(double radius);
    double getRadius();

private:
    double radius_;
};

}  // namespace shape
}  // namespace rt

#endif  // RT_SHAPE_SPHERE_HPP_