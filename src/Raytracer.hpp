#ifndef RT_RAYTRACER
#define RT_RAYTRACER

#include <vector>

#include <libs/Logger.hpp>

#include "scene/Scene.hpp"
#include "core/Color.hpp"


namespace rt
{

// whole dynamic image scaling will be implemented. This one below is only for testing purposes.
#define IMG_WIDTH 1280
#define IMG_HEIGHT 1024


class Raytracer
{
public:
    using Image = std::vector<std::vector<core::Color>>;
    Raytracer() : logger_("Raytracer")
    {
        buffer_.resize(IMG_WIDTH);
        for(int i=0; i<IMG_WIDTH; ++i)
        {
            buffer_[i].resize(IMG_HEIGHT);
        }
    }

    void load(scene::Scene& s);
    void run();
    Image getImage();

private:
    core::Color trace(core::Ray& ray, int reccursionStep);
    Image buffer_;
    scene::Scene scene_;

    Logger logger_;
};

}  // namespace rt


#endif  // RT_RAYTRACER