#ifndef RT_SHAPE_LIGHT_HPP_
#define RT_SHAPE_LIGHT_HPP_

#include <memory>

#include <libs/Logger.hpp>

#include "core/Color.hpp"
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
    using Ptr = std::shared_ptr<Light>;
    Light();

    core::Vector getNormalAt(core::Point& p) override;
    bool hit(core::Ray r, double& dist) override;
    core::Vector UV([[maybe_unused]] const core::Point& p) override;

    void setColor(core::Color color);
    core::Color getColor();

private:
    const core::Material& getMaterialAt([[maybe_unused]] const core::Point& p) override;
    Logger logger_;
    core::Color color_;
};

}  // namespace shape
}  // namespace rt



#endif  // RT_SHAPE_LIGHT_HPP_