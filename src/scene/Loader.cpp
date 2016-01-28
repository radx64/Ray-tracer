#include <exception>
#include <fstream>
#include <iostream>

#include "Loader.hpp"

#include "shape/Sphere.hpp"

namespace rt
{
namespace scene
{

Scene Loader::load(std::string filename)
{
    Scene scene;
    Json::Value root;
    std::ifstream file(filename);
    if (!file) throw std::string("Can't read " + filename);
    file >> root;
    Json::Value sceneNode;
    sceneNode = getOrDie(root, "scene");
    scene.setName(sceneNode.get("name", "Name not set").asString());

    logger_.inf() << "Scene name: "<< scene.getName();


    Json::Value objectsNode;
    objectsNode = getOrDie(sceneNode, "objects");

    for(auto& object : objectsNode)
    {
        logger_.dbg() << "Object: "<< object.get("type","unknown").asString();

        auto objectType = object.get("type", "null").asString();

        // Todo: do someting with that mess
        if (objectType== "sphere")
        {
            Json::Value sphere = object.get("config", "null");
            loadSphere(scene, sphere);
        }
        else
        {
            throw std::string("Unknown object type: ") + objectType;
        }
    }

    return scene;
}

Json::Value Loader::getOrDie(Json::Value node, std::string name)
{
    Json::Value branch = node[name];
    if (branch != "null")
    {
        return branch;
    }   
    else
    {
        throw std::string("Error parsing branch " + name);
        return Json::Value();
    }
}


core::Point Loader::loadPosition(Json::Value& objectNode)
{
    Json::Value position = getOrDie(objectNode, "position");
    double x = position.get("x", "0.0").asDouble();
    double y = position.get("y", "0.0").asDouble();
    double z = position.get("z", "0.0").asDouble();
    return core::Point(x, y, z);    
}

void Loader::loadSphere(Scene& scene, Json::Value& sphereNode)
{
    logger_.dbg()<< "Loading sphere...";
    
    shape::Sphere::Ptr object = std::make_shared<shape::Sphere>();

    core::Point pos = loadPosition(sphereNode);

    double radius = getOrDie(sphereNode, "radius").asDouble();

    object->setPosition(pos);
    object->setRadius(radius);

    scene.addObject(object);
}

}  // namespace scene
}  // namespace rt