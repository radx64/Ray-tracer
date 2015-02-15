#include "Scene.hpp"

namespace rt
{
namespace scene
{

void Scene::addObject(core::Object::Ptr object)
{
    objects_.push_back(object);
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
}  // namespace scene
}  // namespace rt