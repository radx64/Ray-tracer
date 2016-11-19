#ifndef RT_CORE_RAY_HPP_
#define RT_CORE_RAY_HPP_

#include "Point.hpp"
#include "Vector.hpp"

namespace rt
{
namespace core
{

class Ray
{
public:
    explicit Ray(const Point& o, const Vector& dir) : 
    orgin_(o), direction_(dir)
    { }

    Point getOrgin();
    void setOrgin(const Point& p);
    Vector getDirection();
    void setDirection(const Vector& v);
    std::string toString() const;

private:
    Point orgin_;
    Vector direction_;
};

}  // namespace core
}  // namespace rt

#endif  // RT_CORE_RAY_HPP_