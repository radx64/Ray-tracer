#ifndef RT_CORE_RAY_HPP_
#define RT_CORE_RAY_HPP_

#include "Point.hpp"
#include "Vector.hpp"

namespace rt::core {

class Ray {
public:
  Ray(const Point &o, const Vector &dir);

  Point getOrigin();
  void setOrigin(const Point &p);
  Vector getDirection();
  void setDirection(const Vector &v);
  std::string toString() const;

private:
  Point origin_;
  Vector direction_;
};

} // namespace rt::core

#endif // RT_CORE_RAY_HPP_