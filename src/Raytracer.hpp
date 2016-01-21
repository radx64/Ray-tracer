#ifndef RT_RAYTRACER
#define RT_RAYTRACER

#include "scene/Scene.hpp"

#include <vector>

namespace rt
{

// whole dynamic image scaling will be implemented. This one below is only for testing purposes.

#define IMG_SIDE 512

class Raytracer
{
public:
	using ImgType = std::vector<std::vector<double>>;
	Raytracer()
	{
		buffer_.resize(IMG_SIDE);
		for(int i=0; i<IMG_SIDE; ++i)
		{
			buffer_[i].resize(IMG_SIDE);
		}

		hitCounter_ = 0;
		noHitCounter_ = 0;
	}

	void load(scene::Scene& s);
	void run();
	ImgType getImage();

private:
	double trace(core::Ray& ray, int recursiveStep);
	ImgType buffer_;
	scene::Scene scene_;

	int hitCounter_;
	int noHitCounter_;
};

}  // namespace rt


#endif  // RT_RAYTRACER