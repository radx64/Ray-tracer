#include "Material.hpp"

namespace rt::core
{

rt::core::Color Material::get_ambient_at_uv(const double u, const double v) const
{
    return ambient;
}
rt::core::Color Material::get_specular_at_uv(const double u, const double v) const
{
    return specular;
}
rt::core::Color Material::get_diffuse_at_uv(const double u, const double v) const
{
    return diffuse;
}

double Material::get_refraction_index_at_uv(const double u, const double v) const
{
    return refractionIndex;
}
double Material::get_opacity_at_uv(const double u, const double v) const
{
    return opacity;
}


Material::Material(rt::core::Color&& ambient, rt::core::Color&& specular, rt::core::Color&& diffuse,
    double refractionIndex, double opacity)
: ambient(ambient), specular(specular), diffuse(diffuse),
    refractionIndex(refractionIndex), opacity(opacity)
{
}

}  // namespace rt::core