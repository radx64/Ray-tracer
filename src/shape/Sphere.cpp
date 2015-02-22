#include "Sphere.hpp"

#include <cmath>

namespace rt
{
namespace shape
{

void Sphere::setRadius(double radius)
{
    radius_ = radius;
}
double Sphere::getRadius()
{
    return radius_;
}

core::Vector Sphere::getNormalAt(core::Point& p)
{
    core::Vector normal;
    normal = p - getPosition();
    normal.normalize();
    return normal;
}

bool Sphere::Hit(core::Ray r, double& dist)
{
    core::Point p = getPosition() - r.getOrgin();
    core::Vector distance;
    distance = p; 
    double B = r.getDirection() * distance;
    double D = B*B - distance * distance + getRadius() * getRadius(); 
    if (D < 0.0f) return false;
    double t0 = B - sqrtf(D); 
    double t1 = B + sqrtf(D);
    bool retvalue = false;  
    if ((t0 >= 0.5f) && (t0 <= dist))
    {
        dist = t0;
        retvalue = true;
    } 
    if ((t1 >= 0.5f) && (t1 <= dist))                   
    {
        dist = t1; 
        retvalue = true; 
    }

    return retvalue;
}


}  // namespace shape
}  // namespace rt
