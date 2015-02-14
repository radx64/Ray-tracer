#ifndef RT_CORE_OBJECT_HPP_
#define RT_CORE_OBJECT_HPP_

#include <memory>

#include "Point.hpp"

namespace rt
{
namespace core
{

class Object
{
public:
	typedef std::shared_ptr<Object> Ptr;
	enum Type
	{
		Sphere,
		Box
	};

	Object() : position_(0.0,0.0,0.0)
	{ }

	void setPosition(Point& p);
	Point getPosition();

	void setType(Type type);
	Type getType();

private:
	Point position_;
	Type type_;
};

}  // namespace core
}  // namespace rt

#endif  // RT_CORE_OBJECT_HPP_