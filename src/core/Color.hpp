#ifndef RT_CORE_COLOR_HPP_
#define RT_CORE_COLOR_HPP_

#include <string>

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

    std::string toString();

    Color operator + (const Color& c);
    Color operator + (const double& inc);
    Color operator - (const Color& c);
    Color operator * (const double& mult);
    Color operator * (const Color& rhs);

};

}  // namesapce core
}  // namespace rt

#endif  // RT_CORE_COLOR_HPP_