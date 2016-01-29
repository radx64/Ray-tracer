#ifndef RT_CORE_COLOR_HPP_
#define RT_CORE_COLOR_HPP_

namespace rt
{
namespace core
{

class Color
{
public:
    double red;
    double green;
    double blue;

    Color operator + (const Color& c);
    Color operator - (const Color& c);
    Color operator * (const double& mult);

};

}  // namesapce core
}  // namespace rt

#endif  // RT_CORE_COLOR_HPP_