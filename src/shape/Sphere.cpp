#include "Sphere.hpp"

#include <cmath>
#include <algorithm>
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
    core::Vector dist = r.getOrgin() - getPosition();
    double b = dist.dotProduct(r.getDirection());
    double c = (dist.dotProduct(dist)) - (getRadius() * getRadius());
    double d = b*b - c;
    if (d <= 0.0) return false;
    d = sqrtf(d);

    double t1 = - b - d;
    
    if ((t1 > 0.005f) && (t1 < t))
    {
        t = t1;
        return true;
    }

    double t2 = - b + d;

    if ((t2 > 0.005f) && (t2 < t))
    {
        t = t2;
        return true;
    }

    return false;
}

const core::Vector Sphere::UV(const core::Point& p)
{
    // https://en.wikipedia.org/wiki/UV_mapping (for sphere)
    core::Point dist = p - getPosition(); 

    core::Vector point(dist.getX(), dist.getY(), dist.getZ());
    point.normalize();

    double u = atan2(point.getX(), point.getZ());
    double v = atan2(point.getY(), core::Vector{point.getX(), 0.0, point.getZ()}.length());
    u = (u / (2.0 * M_PI)) + 0.5;
    v = 0.5 - asin(point.getY()) / M_PI;
    return core::Vector{u, v, 0.0};
}


}  // namespace shape
}  // namespace rt
