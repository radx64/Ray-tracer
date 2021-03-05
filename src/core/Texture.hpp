#ifndef RT_CORE_TEXTURE_HPP_
#define RT_CORE_TEXTURE_HPP_

#include <memory>
#include <string>
#include <vector>

#include "Color.hpp"
#include "Material.hpp"

namespace rt::core
{

class Texture : public rt::core::Material
{
public:
    Texture(const std::string& filename, const double u_offset, const double v_offset);
    Texture(const rt::core::Material& material, const std::string& filename, const double u_offset, const double v_offset);

    rt::core::Color get_ambient_at_uv(const double u, const double v) const override;
    rt::core::Color get_specular_at_uv(const double u, const double v) const override;
    rt::core::Color get_diffuse_at_uv(const double u, const double v) const override;
    double get_refraction_index_at_uv(const double u, const double v) const override;
    double get_opacity_at_uv(const double u, const double v) const override;

protected:
    unsigned int get_width() const;
    unsigned int get_height() const;
    double get_u_offset() const;
    double get_v_offset() const;

    const rt::core::Color& get_color_at_uv(double u, double v) const;

    unsigned int height_{};
    unsigned int width_{};
    double u_offset_{};
    double v_offset_{};

    // this texture data should be moved somewhere to be reusable later with different materials instances
    // right now hacked on shared_ptr as material is to often copied which slows drastically redering
    // need to get rid of those copies before removing this shared_ptr
    std::shared_ptr<std::vector<std::vector<rt::core::Color>>> color_channel;
};

}

#endif  // RT_CORE_TEXTURE_HPP_