#include "Color.hpp"

namespace rt
{
namespace core
{
    Color::Color(const double r, const double g, const double b)
    : red(r), green(g), blue(b)
    {}

    Color Color::operator + (const Color& c) const
    {
    	return Color{red+c.red, green+c.green, blue+c.blue};
    }

    Color Color::operator + (const double& inc) const
    {
    	return Color{red+inc, green+inc, blue+inc};
    }

    Color Color::operator - (const Color& c) const
    {
    	return Color{red-c.red, green-c.green, blue-c.blue};
    }

    Color Color::operator - (const double& dec) const
    {
    	return Color{red-dec, green-dec, blue-dec};
    }

    Color Color::operator * (const double& mult) const
    {
    	return Color{red*mult, green*mult, blue*mult};
    }

    Color Color::operator * (const Color& rhs) const
    {
    	return Color{red*rhs.red, green*rhs.green, blue*rhs.blue};
    }

    bool Color::operator== (const Color& rhs) const
    {
        return ((red == rhs.red) and (green == rhs.green) and (blue == rhs.blue));
    }

    std::string Color::toString()
    {
        return std::string("["
        + std::to_string(red) + ", "
        + std::to_string(green) + ", "
        + std::to_string(blue) + "]");
    }

}  // namesapce core
}  // namespace rt