#ifndef RT_CORE_MATERIAL_HPP_
#define RT_CORE_MATERIAL_HPP_

#include <memory>

#include "Color.hpp"
#include "Texture.hpp"

namespace rt {
namespace core {

class Material {
public:
  Color ambient;
  Color specular;
  Color diffuse;

  std::shared_ptr<Texture> texture; // later on move to some texture pool;
                                    // right now it will do the trick
  double refractionIndex;
  double opacity;
};

} // namespace core
} // namespace rt

#endif // RT_CORE_MATERIAL_HPP_