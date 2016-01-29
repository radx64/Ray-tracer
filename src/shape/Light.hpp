#ifndef RT_SHAPE_LIGHT_HPP_
#define RT_SHAPE_LIGHT_HPP_

#include <memory>

#include <libs/Logger.hpp>

#include "core/Object.hpp"
#include "core/Vector.hpp"
#include "core/Ray.hpp"

namespace rt
{
namespace shape
{

class Light : public core::Object
{
public:
    typedef std::shared_ptr<Light> Ptr;
    Light();

    core::Vector getNormalAt(core::Point& p) override;
    bool hit(core::Ray r, double& dist) override;

private:
    Logger logger_;
};

}  // namespace shape
}  // namespace rt



#endif  // RT_SHAPE_LIGHT_HPP_