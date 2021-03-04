#ifndef RT_CORE_TEXTURE_HPP_
#define RT_CORE_TEXTURE_HPP_

#include <string>
#include <vector>

#include "Color.hpp"

namespace rt::core
{

class Texture
{
public:
    Texture(const std::string& filename, const double u_offset, const double v_offset);
    std::vector<std::vector<rt::core::Color>> color_channel;

    unsigned int get_width() const;
    unsigned int get_height() const;
    double get_u_offset() const;
    double get_v_offset() const;

    const rt::core::Color& get_color_at(unsigned int x, unsigned int y) const;
    const rt::core::Color& get_color_at_uv(double u, double v) const;

protected:
    unsigned int height_{};
    unsigned int width_{};
    double u_offset_{};
    double v_offset_{};
};

}

#endif  // RT_CORE_TEXTURE_HPP_