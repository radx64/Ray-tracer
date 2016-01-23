#ifndef RT_RAYTRACER
#define RT_RAYTRACER

#include <vector>

#include "scene/Scene.hpp"
#include "Pixel.hpp"

#include <libs/Logger.hpp>

namespace rt
{

// whole dynamic image scaling will be implemented. This one below is only for testing purposes.

#define IMG_SIDE 512

class Raytracer
{
public:
	using Image = std::vector<std::vector<Color>>;
	Raytracer() : logger_("Raytracer")
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
	Image getImage();

private:
	Color trace(core::Ray& ray, int recursiveStep);
	Image buffer_;
	scene::Scene scene_;

	int hitCounter_;
	int noHitCounter_;

	Logger logger_;
};

}  // namespace rt


#endif  // RT_RAYTRACER