#include "Color.hpp"

namespace rt
{
namespace core
{

    Color Color::operator + (const Color& c)
    {
    	return Color{red+c.red, green+c.green, blue+c.blue};
    }

    Color Color::operator - (const Color& c)
    {
    	return Color{red-c.red, green-c.green, blue-c.blue};
    }

    Color Color::operator * (const double& mult)
    {
    	return Color{red*mult, green*mult, blue*mult};
    }

}  // namesapce core
}  // namespace rt