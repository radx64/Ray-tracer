#ifndef RT_CORE_COLOR_HPP_
#define RT_CORE_COLOR_HPP_

#include <string>

namespace rt::core {

class Color {
public:
  double red;
  double green;
  double blue;

  Color() = default;
  Color(const double r, const double g, const double b);

  std::string toString();

  Color operator+(const Color &c) const;
  Color operator+(const double &inc) const;
  Color operator-(const Color &c) const;
  Color operator-(const double &dec) const;
  Color operator*(const double &mult) const;
  Color operator*(const Color &rhs) const;
  bool operator==(const Color &rhs) const;
};

} // namespace rt::core

#endif // RT_CORE_COLOR_HPP_