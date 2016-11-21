#ifndef RT_RAYTRACER
#define RT_RAYTRACER

#include <vector>

#include <libs/Logger.hpp>

#include "scene/Scene.hpp"
#include "core/Color.hpp"


namespace rt
{

// whole dynamic image scaling will be implemented. This one below is only for testing purposes.
#define IMG_SIDE 700

class Raytracer
{
public:
    using Image = std::vector<std::vector<core::Color>>;
    Raytracer() : logger_("Raytracer")
    {
        buffer_.resize(IMG_SIDE);
        for(int i=0; i<IMG_SIDE; ++i)
        {
            buffer_[i].resize(IMG_SIDE);
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