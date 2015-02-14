#include "Object.hpp"

namespace rt
{
namespace core
{

void Object::setPosition(Point& p)
{
	position_ = p;
}

Point Object::getPosition()
{
	return position_;
}

}  // namespace core
}  // namespace return