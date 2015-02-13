#ifndef RT_CORE_VECTOR_HPP_
#define RT_CORE_VECTOR_HPP_

#include "Point.hpp"

namespace rt
{
namespace core
{

class Vector : public Point
{
public:
	explicit Vector(double x, double y, double z) : Point(x, y, z)
	{ }
	Vector crossProduct(const Vector& v);
	bool isZero();
	void normalize();

	Vector operator + (Point& p);
};

}  // namespace core
}  // namespace rt

#endif  // RT_CORE_VECTOR_HPP_