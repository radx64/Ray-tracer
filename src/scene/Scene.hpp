#ifndef RT_SCENE_SCENE_HPP_
#define RT_SCENE_SCENE_HPP_

#include <vector>
#include <string>

#include "core/Object.hpp"
#include "shape/Light.hpp"
#include "core/Camera.hpp"

namespace rt::scene
{

class Scene
{
public:
    Scene()
    { }
    void addObject(core::Object::Ptr object);
    void addLight(shape::Light::Ptr light);

    void setName(std::string name);
    const std::string& getName();
    std::vector<core::Object::Ptr>& getObjects();
    std::vector<shape::Light::Ptr>& getLights();
    void setCamera(const core::Camera& camera);
    const core::Camera& getCamera();

private:
    std::vector<core::Object::Ptr> objects_;
    std::vector<shape::Light::Ptr> lights_;
    core::Camera camera_;
    std::string name_;
};

}  // namespace rt::scene

#endif  // RT_SCENE_SCENE_HPP_