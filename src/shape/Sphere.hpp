#ifndef RT_SHAPE_SPHERE_HPP_
#define RT_SHAPE_SPHERE_HPP_

#include <memory>

#include <libs/Logger.hpp>

#include "core/Object.hpp"
#include "core/Vector.hpp"

namespace rt::shape {

class Sphere : public core::Object {
public:
  using Ptr = std::shared_ptr<Sphere>;

  Sphere() = default;

  core::Vector getNormalAt(core::Point &p) override;
  bool hit(core::Ray r, double &dist) override;

  void setRadius(double radius);
  double getRadius();

  core::Vector UV(const core::Point &p) override;
  const core::Material &
  getMaterialAt([[maybe_unused]] const core::Point &p) override;

private:
  double radius_;
};

} // namespace rt::shape

#endif // RT_SHAPE_SPHERE_HPP_