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
    const core::Vector p =  r.getOrgin() - getPosition();
    core::Vector distance;  
    distance = p;
    double B = r.getDirection().dotProduct(distance);
    double D = B*B - distance.dotProduct(distance) + (getRadius() * getRadius()); 
    if (D < 0.0) return false;
    double t0 = B - sqrtf(D); 
    double t1 = B + sqrtf(D);

    //std::cout << "distance " << distance << std::endl;
    //std::cout << "B  " << B << std::endl;
    //std::cout << "D  " << D << std::endl;
    // std::cout << "t0 " << t0 << std::endl;
    // std::cout << "t1 " << t1 << std::endl;

    bool retvalue = false;  
    if ((t0 > 0.5) && (t0 <= dist))
    {
        dist = t0;
        // std::cout << "Hit to sphere : t0 "<< t0 << std::endl;
        retvalue = true;
    } 
    if ((t1 > 0.5) && (t1 <= dist))                   
    {
        dist = t1;
        // std::cout << "Hit to sphere : t1 "<< t1 << std::endl;
        retvalue = true; 
    }

    return retvalue;
}

}  // namespace shape
}  // namespace rt
