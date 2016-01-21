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
    std::cout << "Radius set to " << radius << std::endl;
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

// bool Sphere::hit(core::Ray r, double& dist)
// {
//     const core::Vector p = r.getOrgin() - getPosition();
//     core::Vector distance;  
//     distance = p;
//     double B = distance.dotProduct(r.getDirection());
//     double D = B*B - distance.dotProduct(distance) + (getRadius() * getRadius()); 
//     if (D < 0.0f) return false;
//     double t0 = B - sqrtf(D); 
//     double t1 = B + sqrtf(D); 

//     if(t0 > t1) std::swap(t0, t1);

//     if(t0 < 0.0f)
//     {
//         t0 = t1;
//         if (t0 < 1.0f ) return false;
//     }

//     if(t0 < dist)
//     {
//         dist = t0;
//     }

//     //dist = t0;
//     return true;

// }

bool Sphere::hit(core::Ray r, double& dist)
{
    core::Vector to = getPosition() - r.getOrgin();
    double b = to.dotProduct(r.getDirection());
    double c = to.dotProduct(to) - getRadius()*getRadius();
    double d = b*b - c;
    if (d < 0) return false;
    d = sqrtf(d);
    double t0 = - b - d;
    double t1 = - b + d;

    if (t0 > 0 && t0 < t1) t1 = t0;

    if (t1 > 1)
    {
        if(t1 < dist) dist = t1;
        return true;
    }
}


}  // namespace shape
}  // namespace rt
