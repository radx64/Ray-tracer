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
	

	for(int height=0; height<IMG_SIDE; height++)
	{
		for(int width=-IMG_SIDE/2; width<IMG_SIDE/2; width++)
		{
      		// float fovx = 45.0*(M_PI/180.0);
	    	// float fovy = 45.0*(M_PI/180.0);

	    	// float x_fl = (float)height*100/(float)IMG_SIDE;
      		// float y_fl = (float)width*100/(float)IMG_SIDE;

	    	// float aspectRatio = IMG_SIDE/IMG_SIDE;

	    	//core::Point orgin(0.0, 0.0, 0.0);

	    	// core::Vector direction((x_fl)*tan(fovx/2.0),(y_fl)*tan(fovy/2.0),1.0);
	    	// direction.normalize();	//its now normalized but won't be when perspective will be added


	    	core::Point orgin(width, height, 0.0);
	    	core::Vector direction(0.0,0.0,-1.0);

	    	core::Ray viewRay(orgin, direction);

	    	double distance = trace(viewRay, 1);
	    	std::cout << distance << "  ";
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