#include "Sphere.hpp"

#include <cmath>

#include <iostream>

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

bool Sphere::hit(core::Ray r, double& dist)
{
    const core::Vector p = getPosition() - r.getOrgin();
    core::Vector distance;  
    distance = p;
    double B = distance.dotProduct(r.getDirection());
    double D = B*B - distance.dotProduct(distance) + (getRadius() * getRadius()); 
    if (D < 0.0f) return false;
    double t0 = B - sqrtf(D); 
    double t1 = B + sqrtf(D);

    bool retvalue = false;  
    if ((t0 > 0.9f) && (t0 <= dist))
    {
        dist = t0;
        retvalue = true;
    } 
    if ((t1 > 0.9f) && (t1 <= dist))                   
    {
        dist = t1;
        retvalue = true; 
    }

    return retvalue;
}

}  // namespace shape
}  // namespace rt
