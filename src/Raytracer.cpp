#include "Raytracer.hpp"

#include <cmath>
#include <iostream>


namespace rt
{

Raytracer::Image Raytracer::getImage()
{
    return buffer_;
}

void Raytracer::load(scene::Scene& s)
{
    scene_ = s;
}

void Raytracer::run()
{
    for(int height=-IMG_SIDE/2; height < IMG_SIDE/2; height++)
    {
        for(int width =- IMG_SIDE/2; width<IMG_SIDE/2; width++)
        {
            core::Point orgin(width, height, 0.0);
            core::Vector direction(0.0,0.0,-1.0);

            core::Ray viewRay(orgin, direction);

            Color c = trace(viewRay, 1);
            buffer_[width+IMG_SIDE/2][height+IMG_SIDE/2] = c;
        }
    }
    logger_.dbg() << "Hit: " << hitCounter_;
    logger_.dbg() << "NoHit: " << noHitCounter_;
}

Color Raytracer::trace(core::Ray& ray, int recursiveStep)
{
    Color local;

    double distance = 1000000.0f;

    auto objects = scene_.getObjects();

    for(auto& object : objects)
    {

        if(object->hit(ray, distance))
        {
            hitCounter_++;
        }
        else
        {
            noHitCounter_++;    
        }
    };

    if (distance < 1) 
    {
        distance = 1000000.0f;
    }

    Color c = {distance, distance, distance};
    return c;
}



}  // namespace rt