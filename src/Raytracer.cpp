#include "Raytracer.hpp"

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
		for(int width=0; width<IMG_SIDE; width++)
		{
			buffer_[width][height] = static_cast<double>(height*width/4.0);
		}
	}
}
}  // namespace rt