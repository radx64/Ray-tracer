#ifndef RT_SCENE_SCENE_HPP_
#define RT_SCENE_SCENE_HPP_

#include <vector>
#include <string>

#include "core/Object.hpp"
#include "shape/Light.hpp"

namespace rt
{
namespace scene
{

class Scene
{
public:
    Scene()
    { }
    void addObject(core::Object::Ptr object);
    void addLight(shape::Light::Ptr light);

    void setName(std::string name);
    std::string getName();
    std::vector<core::Object::Ptr> getObjects();
    std::vector<shape::Light::Ptr> getLights();

private:
    std::vector<core::Object::Ptr> objects_;
    std::vector<shape::Light::Ptr> lights_;
    std::string name_;
};

}  // namespace scene
}  // namespace rt

#endif  // RT_SCENE_SCENE_HPP_