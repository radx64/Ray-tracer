#ifndef RT_CORE_POINT_HPP_
#define RT_CORE_POINT_HPP_

#include <ostream>

namespace rt
{
namespace core
{

class Point
{
public:
	explicit Point(double x, double y, double z):
	x_(x), y_(y), z_(z)
	{ }

	double getX() const;
	double getY() const;
	double getZ() const;

	void setX(double x);
	void setY(double y);
	void setZ(double z);

	Point operator + (const Point& p);
	Point operator - (const Point& p);
	double operator * (const Point& p);

protected:
	double x_;
	double y_;
	double z_;
};

std::ostream& operator<< (std::ostream& s, Point p);

}  // namespace core
}  // namespace rt 

#endif  // RT_CORE_POINT_HPP_