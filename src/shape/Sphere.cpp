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
    core::Vector normal (p - getPosition());
    normal.normalize();
    return normal;
}

bool Sphere::hit(core::Ray r, double& t)
{
    core::Vector dist = getPosition() - r.getOrgin();
    double b = dist.dotProduct(r.getDirection());
    double d = b*b - dist.dotProduct(dist) + getRadius() * getRadius();
    if (d < 0.0f) return false;
    d = sqrtf(d);
    double t0 = b - d;
    double t1 = b + d;

    if (t0 >= -0.5f && t0 < t)
    {
        t = t0;
    }

    if (t1 > -0.5f)
    {
        if(t1 < t) t = t1;
        return true;
    }
}


}  // namespace shape
}  // namespace rt
