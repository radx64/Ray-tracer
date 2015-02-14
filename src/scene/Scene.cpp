#include "Scene.hpp"

namespace rt
{
namespace scene
{

void Scene::addObject(core::Object::Ptr object)
{
    Objects_.push_back(object);
}

void Scene::setName(std::string name)
{
    name_ = name;
}
std::string Scene::getName()
{
    return name_;
}

}  // namespace scene
}  // namespace rt