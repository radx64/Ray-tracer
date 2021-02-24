#include "Sphere.hpp"

#include <cmath>
#include <algorithm>
#include <iostream>

namespace rt::shape
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
    core::Vector dist = r.getOrigin() - getPosition();
    double b = dist.dot(r.getDirection());
    double c = (dist.dot(dist)) - (getRadius() * getRadius());
    double d = b*b - c;
    if (d <= 0.0) return false;

    d = sqrt(d);

    double t1 = - b - d;
    double t2 = - b + d;

    if ((t1 > 0.005f) && (t1 < t))
    {
        t = t1;
        return true;
    }

    if ((t2 > 0.005f) && (t2 < t))
    {
        t = t2;
        return true;
    }
    return false;
}

core::Vector Sphere::UV(const core::Point& p)
{
    // https://en.wikipedia.org/wiki/UV_mapping (for sphere)
    core::Point dist = p - getPosition(); 

    core::Vector point(dist.x(), dist.y(), dist.z());
    point.normalize();

    double u = atan2(point.x(), point.z());
    double v = atan2(point.y(), core::Vector{point.x(), 0.0, point.z()}.length());
    u = (u / (2.0 * M_PI)) + 0.5;
    v = 0.5 - asin(point.y()) / M_PI;
    return core::Vector{u, v, 0.0};
}

const core::Material& Sphere::getMaterialAt([[maybe_unused]] const core::Point& p)
{
    return Object::getMaterial();
}

}  // namespace rt::shape
