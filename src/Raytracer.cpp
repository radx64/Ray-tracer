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
            core::Vector direction(0.0,0.0, -1.0);

            core::Ray viewRay(orgin, direction);

            core::Color c = trace(viewRay, 1);

            /* need to implement some exponential color clamping */
            if (c.red > 255) c.red = 255;
            if (c.green > 255) c.green = 255;
            if (c.blue > 255) c.blue = 255; 

            if (c.red < 0) c.red = 0;
            if (c.green < 0) c.green = 0;
            if (c.blue < 0) c.blue = 0; 

            buffer_[width+IMG_SIDE/2][height+IMG_SIDE/2] = c;
        }
    }

    for(int height=-IMG_SIDE/2; height < IMG_SIDE/2; height++)
    {
        for(int width =- IMG_SIDE/2; width<IMG_SIDE/2; width++)
        {
            core::Color c = buffer_[width+IMG_SIDE/2][height+IMG_SIDE/2];
            buffer_[width+IMG_SIDE/2][height+IMG_SIDE/2] = c;
        }
    }

    logger_.dbg() << "Hit: " << hitCounter_;
    logger_.dbg() << "NoHit: " << noHitCounter_;
    logger_.inf() << "Hit ratio: " << (static_cast<float>(hitCounter_)/(hitCounter_+ noHitCounter_) * 100.0) << "\%";
}

core::Color Raytracer::trace(core::Ray& ray, int recursiveStep)
{
    core::Color local = {0.0,0.0,0.0};

    double distance = 10000.0f;

    auto objects = scene_.getObjects();

    core::Object::Ptr closestObject = nullptr;

    for(auto& object : objects)
    {

        double temporaryDistance = distance;

        if(object->hit(ray, temporaryDistance))
        {
            hitCounter_++;
            if(temporaryDistance < distance)
            {
                distance = temporaryDistance;
                closestObject = object;
            }

        }
        else
        {
            noHitCounter_++;    
        }
    };

    if (closestObject == nullptr)
    {
        return core::Color{0.0,0.0,0.0};
    }

    core::Point collision = ray.getOrgin() + ray.getDirection() * distance;
    core::Vector normal = closestObject->getNormalAt(collision);

    auto lights = scene_.getLights();
    for(auto& light : lights)
    {

        // PHONG lighting model
        double a = 1.0;
        double b = 0.01;
        double c = 0.01;

        core::Vector V = ray.getDirection();    // observation vector
        core::Vector L = collision - light->getPosition(); // light incidence vector
        V.normalize();
        L.normalize();

        double dotNL = normal.dotProduct(L);

        core::Vector R = L - (normal * (2.0 * dotNL));    //reflected vector
        R.normalize();

        double dotVR = V.dotProduct(R) ; // angle betwen observation vector and reflected vector

        core::Vector difference = collision - light->getPosition();

        double di = sqrtf(
            difference.getX() * difference.getX() +
            difference.getY() * difference.getY() + 
            difference.getZ() * difference.getZ());


        double lightning_factor = 1.0 / (a + b*di + c*di*di);
        local = local + closestObject->getMaterial().ambient + light->getColor() * lightning_factor
        + closestObject->getMaterial().diffuse * light->getColor()  * dotNL * 0.03
        + closestObject->getMaterial().specular * light->getColor() * pow(dotVR, 180);
        ;
    }

    return local;
}



}  // namespace rt