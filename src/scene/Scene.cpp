#include "Scene.hpp"

namespace rt::scene {

void Scene::addObject(core::Object::Ptr object) { objects_.push_back(object); }

void Scene::addLight(shape::Light::Ptr light) { lights_.push_back(light); }

void Scene::setName(std::string name) { name_ = name; }
const std::string &Scene::getName() { return name_; }

std::vector<core::Object::Ptr> &Scene::getObjects() { return objects_; }

std::vector<shape::Light::Ptr> &Scene::getLights() { return lights_; }

void Scene::setCamera(const core::Camera &camera) { camera_ = camera; }
const rt::core::Camera &Scene::getCamera() { return camera_; }

} // namespace rt::scene