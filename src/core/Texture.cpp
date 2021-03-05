#include "Texture.hpp"

#include <cmath>
#include <memory>

#include <png++/png.hpp>

namespace rt::core
{
Texture::Texture(const rt::core::Material& material, const std::string& filename, const double u_offset, const double v_offset) 
: Material(material), u_offset_(u_offset), v_offset_(v_offset)
{
    png::image<png::rgb_pixel> image(filename);
    width_ = image.get_width();
    height_ = image.get_height();  

    color_channel = std::make_shared<std::vector<std::vector<rt::core::Color>>>();

    color_channel->resize(height_);
    for (unsigned int i=0; i<height_; ++i)
    {
        (*color_channel)[i].resize(width_);
    }

    for (unsigned int x = 0; x < width_; ++x)
    {
        for (unsigned int y = 0; y < height_; ++y)
        {
            const auto& pixel = image.get_pixel(x,y);
            (*color_channel)[y][x].red = pixel.red;
            (*color_channel)[y][x].green = pixel.green;
            (*color_channel)[y][x].blue = pixel.blue;
        }
    }
}

Texture::Texture(const std::string& filename, const double u_offset, const double v_offset)
: Texture(Material(), filename, u_offset, v_offset)
{
}

rt::core::Color Texture::get_ambient_at_uv(const double u, const double v) const
{
    return get_color_at_uv(u,v) + ambient;
}

rt::core::Color Texture::get_specular_at_uv(const double u, const double v) const
{
    return Color(0.0,0.0,0.0); // get_color_at_uv(u,v) + specular;
}

rt::core::Color Texture::get_diffuse_at_uv(const double u, const double v) const
{
    return get_color_at_uv(u,v) + diffuse;
}

double Texture::get_refraction_index_at_uv(const double u, const double v) const
{
    return refractionIndex;
}
double Texture::get_opacity_at_uv(const double u, const double v) const
{
    return opacity;
}

unsigned int Texture::get_width() const
{
    return width_;
}
unsigned int Texture::get_height() const
{
    return height_;
}

const rt::core::Color& Texture::get_color_at_uv(double u, double v) const
{
    double normalized_u = fmod(u + get_u_offset(), 1.0);
    double normalized_v = fmod(v + get_v_offset(), 1.0);
    unsigned int x = normalized_u * get_width();
    unsigned int y = normalized_v * get_height(); 
    return (*color_channel)[y][x];
}
double Texture::get_u_offset() const
{
    return u_offset_;
}
double Texture::get_v_offset() const
{
    return v_offset_;
}

}  // namespace core