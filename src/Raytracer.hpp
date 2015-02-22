#ifndef RT_RAYTRACER
#define RT_RAYTRACER

#include "scene/Scene.hpp"

#include <vector>

namespace rt
{

// whole dynamic image scaling will be implemented. This one below is only for testing purposes.

#define IMG_SIDE 128

class Raytracer
{
public:
	typedef std::vector<std::vector<double>> ImgType;
	Raytracer()
	{
		buffer_.resize(IMG_SIDE);
		for(int i=0; i<IMG_SIDE; ++i)
		{
			buffer_[i].resize(IMG_SIDE);
		}
	}

	void load(scene::Scene& s);
	void run();
	ImgType getImage();

private:
	double trace(core::Ray& ray, int recursiveStep);
	ImgType buffer_;
	scene::Scene scene_;
};

}  // namespace rt


#endif  // RT_RAYTRACER