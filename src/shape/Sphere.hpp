#ifndef RT_SHAPE_SPHERE_HPP_
#define RT_SHAPE_SPHERE_HPP_

#include <memory>

#include <libs/Logger.hpp>

#include "core/Object.hpp"
#include "core/Vector.hpp"

namespace rt
{
namespace shape
{

class Sphere : public core::Object
{
public:
    using Ptr = std::shared_ptr<Sphere>;
    
    Sphere() : logger_("Sphere")
    { }

    virtual core::Vector getNormalAt(core::Point& p);
    virtual bool hit(core::Ray r, double& dist);

    void setRadius(double radius);
    double getRadius();

private:
    double radius_;
    Logger logger_;
};

}  // namespace shape
}  // namespace rt

#endif  // RT_SHAPE_SPHERE_HPP_