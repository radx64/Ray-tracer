#ifndef RT_CORE_OBJECT_HPP_
#define RT_CORE_OBJECT_HPP_

#include <memory>

#include "Point.hpp"
#include "Ray.hpp"

namespace rt
{
namespace core
{

class Object
{
public:
    typedef std::shared_ptr<Object> Ptr;

    Object() : position_(0.0,0.0,0.0)
    { }

    void setPosition(Point& p);
    Point getPosition();

    virtual Vector getNormalAt(Point& p) = 0;
    virtual bool Hit(Ray r, double& dist) = 0;


private:
    Point position_;
};

}  // namespace core
}  // namespace rt

#endif  // RT_CORE_OBJECT_HPP_