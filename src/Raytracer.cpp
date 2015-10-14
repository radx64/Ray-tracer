#include "Raytracer.hpp"

#include <cmath>

#include <iostream>

namespace rt
{

Raytracer::ImgType Raytracer::getImage()
{
	return buffer_;
}

void Raytracer::load(scene::Scene& s)
{
	scene_ = s;
}

void Raytracer::run()
{
	for(int height=0; height < IMG_SIDE; height++)
	{
		for(int width =- IMG_SIDE/2; width<IMG_SIDE/2; width++)
		{
	    	core::Point orgin(width, height, 0.0);
	    	core::Vector direction(0.0,0.0,-1.0);

	    	core::Ray viewRay(orgin, direction);

	    	double distance = trace(viewRay, 1);
	    	buffer_[width+IMG_SIDE/2][height] = distance;
		}
	}
}

double Raytracer::trace(core::Ray& ray, int recursiveStep)
{
	double distance = 1000000.0;

	auto objects = scene_.getObjects();

	for(auto& object : objects)
	{
		if(object->hit(ray, distance));
		{
			//std::cout << "HIT!" << std::endl;
		}
		//std::cout << ray.getOrgin() << std::endl;
		//std::cout << distance << std::endl;
	};

	return distance;
}



}  // namespace rt