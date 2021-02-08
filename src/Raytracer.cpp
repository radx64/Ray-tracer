#include "Raytracer.hpp"

#include <cmath>
#include <iostream>

namespace rt
{

core::Color clamp(core::Color c)
{
    /* need to implement some exponential color clamping or something*/

    if (c.red > 255) c.red = 255;
    if (c.green > 255) c.green = 255;
    if (c.blue > 255) c.blue = 255; 

    if (c.red < 0) c.red = 0;
    if (c.green < 0) c.green = 0;
    if (c.blue < 0) c.blue = 0;

    return c;
}

static const int maxReccursionLimit = 3;

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
    const auto camera_fov = scene_.getCamera().fov_;

    double fovx = camera_fov.getX()*(M_PI/180.0);
    double fovy = camera_fov.getY()*(M_PI/180.0);

    double hd;
    double wd;

    for(int height=-IMG_HEIGHT/2; height < IMG_HEIGHT/2; height++)
    {
        for(int width =- IMG_WIDTH/2; width<IMG_WIDTH/2; width++)
        {
            const auto camera_position = scene_.getCamera().position_;

            core::Point origin(
                camera_position.getX() + width,
                camera_position.getY() + height, 
                camera_position.getZ() + 0.0);

            hd = (float)height/(IMG_HEIGHT); 
            wd = (float)width/(IMG_WIDTH);

            core::Vector direction((wd)*tan(fovx/2), (hd)*tan(fovy/2), 1.0);
            direction.normalize();

            core::Ray viewRay(origin, direction);

            core::Color c = trace(viewRay, 0);

            buffer_[width+IMG_WIDTH/2][height+IMG_HEIGHT/2] = clamp(c);
        }
        std::cout << "Render progress: " << (height + IMG_HEIGHT/2)*100 / IMG_HEIGHT << "%" << "\r";     
    }
}

core::Color Raytracer::trace(core::Ray& ray, int reccursionStep)
{
    core::Color local = {0.0,0.0,0.0};

    if (reccursionStep > maxReccursionLimit) return local;

    double distance = 10000.0f;

    auto objects = scene_.getObjects();

    core::Object::Ptr closestObject = nullptr;

    for(auto& object : objects)
    {
        if(object->hit(ray, distance)) closestObject = object;
    };

    if (closestObject == nullptr) return core::Color{30.0, 30.0, 30.0};

    core::Point collision = ray.getOrgin() + ray.getDirection() * distance;
    core::Vector normal = closestObject->getNormalAt(collision);

    core::Material closestObjectMaterial = closestObject->getMaterialAt(collision);
    core::Vector closestObjectUV = closestObject->UV(collision);

    // checkered pattern fo UV map testing
    bool checkered = false;
    float sines = cos(M_PI*40 * closestObjectUV.getX()) * cos(M_PI*40.0 * closestObjectUV.getY());
    if (sines < 0) checkered = true;

    auto lights = scene_.getLights();
    for(auto& light : lights)
    {

        // PHONG lighting model
        double a = 1.0;
        double b = 0.1;
        double c = 0.001;

        core::Vector V = ray.getDirection();    // observation vector
        V.normalize();
        core::Vector L = light->getPosition() - collision; // light incidence vector
        L.normalize();

        double t2 = sqrtf(L.dotProduct(L));
        core::Vector lightDirection = L * (2.0f/t2);
        lightDirection.normalize();
        core::Ray lightRay(collision, lightDirection);

        bool isInShadow = false;

        for(auto& object : objects)
        {
            if(object->isCastingShadow && object->hit(lightRay, t2))
            {
                //isInShadow = true;
                break;
            }
        };

        double dotNL = normal.dotProduct(L) ;

        core::Vector R = L - (normal * dotNL * 2.0);   //reflected vector
        R.normalize();

        double dotVR = V.dotProduct(R) ; // angle betwen observation vector and reflected vector

        if (dotVR < 0) dotVR = 0;

        core::Vector difference = light->getPosition() - collision;

        double di = sqrtf(
            difference.getX() * difference.getX() +
            difference.getY() * difference.getY() + 
            difference.getZ() * difference.getZ());

        double lightning_factor = 1.0 / (a + b*di + c*di*di);

        if (isInShadow)
        {
            local = local + clamp(closestObjectMaterial.ambient * lightning_factor);
            local = core::Color{255.0,0.0,255.0};
        }
        else
        {
            core::Color ambient = closestObjectMaterial.ambient * lightning_factor;
            core::Color diffuse = closestObjectMaterial.diffuse * light->getColor()  * dotNL * lightning_factor * 10.0;
            core::Color specular = closestObjectMaterial.specular * light->getColor() * pow(dotVR, 40) * 0.95;
        
            if (checkered)
            {
                diffuse = diffuse * 2.0;
            }

            local = local + clamp(ambient) + clamp(diffuse) + clamp(specular);
        }
    }

    core::Ray reflected(collision, ray.getDirection() - normal * (ray.getDirection().dotProduct(normal)) * 2.0);
    core::Color reflectedColor = trace(reflected, reccursionStep + 1);
    local = local + clamp(reflectedColor * 0.3);    // todo: reflection factor as paramter

    if (closestObjectMaterial.opacity > 0.0)    //comparing doubles should use some kind of epsilon (std::numeric_limis<double> maybe?)
    {
        double n1;
        double n2;
        double cosI = ray.getDirection().dotProduct(normal);

        if (cosI > 0)
        {
            n1 = closestObjectMaterial.refractionIndex;
            n2 = 1.0f;
        }
        else
        {
            n1 = 1.0f;  
            n2 = closestObjectMaterial.refractionIndex;
            cosI = -cosI;
        }

        double cosT = 1.0f - pow(n1/n2, 2.0f) * (1.0f - pow(cosI, 2.0f));

        if (cosT < 0.0f)
        {
            // This is total internal reflection (but i'm lazy so it still refracting)
            // todo: fix me
            core::Ray refraction(collision, 
                ray.getDirection() * (n1/n2) + normal * ((n1/n2) * cosI - cosT));

            core::Color refractionColor = trace(refraction, reccursionStep + 1);
            local = local + clamp(refractionColor * closestObjectMaterial.opacity);

        }
        else
        {
            core::Ray refraction(collision, 
                ray.getDirection() * (n1/n2) + normal * ((n1/n2) * cosI - cosT));

            core::Color refractionColor = trace(refraction, reccursionStep + 1);
            local = local + clamp(refractionColor * closestObjectMaterial.opacity);

        }
    }
    return local;
}



}  // namespace rt