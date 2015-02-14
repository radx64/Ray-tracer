#ifndef RT_CORE_OBJECT_HPP_
#define RT_CORE_OBJECT_HPP_

#include "Point.hpp"

namespace rt
{
namespace core
{

class Object
{
public:
	void setPosition(Point& p);
	Point getPosition();

private:
	Point position_;
};

}  // namespace core
}  // namespace rt

#endif  // RT_CORE_OBJECT_HPP_