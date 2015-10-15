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
	for(int height=-IMG_SIDE/2; height < IMG_SIDE/2; height++)
	{
		for(int width =- IMG_SIDE/2; width<IMG_SIDE/2; width++)
		{
	    	core::Point orgin(width, height, 0.0);
	    	core::Vector direction(0.0,0.0,-1.0);

	    	core::Ray viewRay(orgin, direction);

	    	double distance = trace(viewRay, 1);
	    	buffer_[width+IMG_SIDE/2][height+IMG_SIDE/2] = distance;
		}
	}
}

double Raytracer::trace(core::Ray& ray, int recursiveStep)
{
	double distance = 100000000.0;

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