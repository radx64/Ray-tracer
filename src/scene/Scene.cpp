#include "Scene.hpp"

namespace rt
{
namespace scene
{

void Scene::addObject(core::Object::Ptr object)
{
    objects_.push_back(object);
}

void Scene::addLight(shape::Light::Ptr light)
{
    lights_.push_back(light);
}

void Scene::setName(std::string name)
{
    name_ = name;
}
std::string Scene::getName()
{
    return name_;
}

std::vector<core::Object::Ptr> Scene::getObjects()
{
    return objects_;
}

std::vector<shape::Light::Ptr> Scene::getLights()
{
    return lights_;
}
}  // namespace scene
}  // namespace rt