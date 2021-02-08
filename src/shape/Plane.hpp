#ifndef RT_SHAPE_PLANE_HPP_
#define RT_SHAPE_PLANE_HPP_

#include <memory>

#include <libs/Logger.hpp>

#include "core/Object.hpp"
#include "core/Vector.hpp"

namespace rt
{
namespace shape
{

class Plane : public core::Object
{
public:
    using Ptr = std::shared_ptr<Plane>;
    
    Plane() : logger_("Plane")
    {
        isCastingShadow = false; 
    }

    core::Vector getNormalAt(core::Point& p) override;
    bool hit(core::Ray r, double& dist) override;
    const core::Vector UV(const core::Point& p) override; 

private:
    Logger logger_;
};

}  // namespace shape
}  // namespace rt

#endif  // RT_SHAPE_PLANE_HPP_