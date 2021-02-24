#ifndef RT_CORE_OBJECT_HPP_
#define RT_CORE_OBJECT_HPP_

#include <memory>

#include "Material.hpp"
#include "Point.hpp"
#include "Ray.hpp"

namespace rt {
namespace core {

class Object {
public:
  using Ptr = std::shared_ptr<Object>;

  Object() : position_(0.0, 0.0, 0.0) {}

  void setMaterial(Material material);
  const Material &getMaterial();

  void setPosition(Point &p);
  Point getPosition();

  virtual Vector getNormalAt(Point &p) = 0;
  virtual bool hit(Ray r, double &dist) = 0;
  virtual core::Vector UV(const Point &p) = 0;
  virtual const core::Material &getMaterialAt(const Point &p) = 0;

  bool isCastingShadow = true;

private:
  Point position_;
  Material material_;
};

} // namespace core
} // namespace rt

#endif // RT_CORE_OBJECT_HPP_