#ifndef RT_CORE_MATERIAL_HPP_
#define RT_CORE_MATERIAL_HPP_

#include "Color.hpp"

namespace rt {
namespace core {

class Material {
public:
  Color ambient;
  Color specular;
  Color diffuse;

  double refractionIndex;
  double opacity;
};

} // namespace core
} // namespace rt

#endif // RT_CORE_MATERIAL_HPP_