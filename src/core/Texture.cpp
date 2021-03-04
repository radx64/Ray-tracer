#include "Texture.hpp"
#include <cmath>
#include <png++/png.hpp>

namespace rt::core
{
Texture::Texture(const std::string& filename, const double u_offset, const double v_offset) 
: u_offset_(u_offset), v_offset_(v_offset)
{
    png::image<png::rgb_pixel> image(filename);
    width_ = image.get_width();
    height_ = image.get_height();    
    color_channel.resize(height_);
    for (unsigned int i=0; i<height_; ++i)
    {
        color_channel[i].resize(width_);
    }

    for (unsigned int x = 0; x < width_; ++x)
    {
        for (unsigned int y = 0; y < height_; ++y)
        {
            const auto& pixel = image.get_pixel(x,y);
            color_channel[y][x].red = pixel.red;
            color_channel[y][x].green = pixel.green;
            color_channel[y][x].blue = pixel.blue;
        }
    }
}

unsigned int Texture::get_width() const
{
    return width_;
}
unsigned int Texture::get_height() const
{
    return height_;
}
const rt::core::Color& Texture::get_color_at(unsigned int x, unsigned int y) const
{
    return color_channel[y][x];
}

const rt::core::Color& Texture::get_color_at_uv(double u, double v) const
{
    double normalized_u = fmod(u + get_u_offset(), 1.0);
    double normalized_v = fmod(v + get_v_offset(), 1.0);
    unsigned int x = normalized_u * get_width();
    unsigned int y = normalized_v * get_height(); 
    return color_channel[y][x];
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