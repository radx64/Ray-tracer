#ifndef RT_CORE_MATERIAL_HPP_
#define RT_CORE_MATERIAL_HPP_

#include "Color.hpp"

namespace rt::core {

class Material {
public:
  virtual ~Material() = default;
  Material() = default;
  virtual rt::core::Color get_ambient_at_uv(const double u, const double v) const;
  virtual rt::core::Color get_specular_at_uv(const double u, const double v) const;
  virtual rt::core::Color get_diffuse_at_uv(const double u, const double v) const;
  virtual double get_refraction_index_at_uv(const double u, const double v) const;
  virtual double get_opacity_at_uv(const double u, const double v) const;

  Material(rt::core::Color&& ambient, rt::core::Color&& specular, rt::core::Color&& diffuse,
    double refractionIndex, double opacity);

protected:
  Color ambient;
  Color specular;
  Color diffuse;
  double refractionIndex;
  double opacity;
};

} // namespace rt::core

#endif // RT_CORE_MATERIAL_HPP_