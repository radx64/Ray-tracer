#ifndef RT_CORE_POINT_HPP_
#define RT_CORE_POINT_HPP_

#include <ostream>

namespace rt::core
{

class Point
{
public:
    Point(double x, double y, double z): x_(x), y_(y), z_(z)
    { }

    Point(): x_(0.0), y_(0.0), z_(0.0)
    { }

    double x() const;
    double y() const;
    double z() const;

    void x(double x);
    void y(double y);
    void z(double z);

    Point operator + (const Point& p) const;
    Point operator - (const Point& p) const;
    double dot(const Point& p) const;
    Point operator*(const double& scale) const;
    bool operator== (const Point& p) const;
    
    std::string toString() const;

protected:
    double x_;
    double y_;
    double z_;
};

std::ostream& operator<< (std::ostream& s, Point p);

}  // namespace rt::core

#endif  // RT_CORE_POINT_HPP_