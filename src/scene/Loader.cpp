#include <exception>
#include <fstream>
#include <iostream>

#include "Loader.hpp"

#include "core/Material.hpp"
#include "core/Camera.hpp"
#include "shape/Sphere.hpp"
#include "shape/Plane.hpp"
#include "shape/Light.hpp"

namespace rt
{
namespace scene
{

Loader::Loader() : logger_("Loader")
{
    objectMapping = 
    {
        {"sphere", ObjectType::Sphere},
        {"plane", ObjectType::Plane},
        {"light" , ObjectType::Light}
    };
}

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

    auto cameraNode = getOrDie(sceneNode, "camera");
    core::Point camera_position = loadPosition(cameraNode);
    core::Vector camera_rotation = loadRotation(cameraNode);
    core::Vector camera_fov = loadFov(cameraNode);
    scene.setCamera(rt::core::Camera{camera_position, camera_rotation, camera_fov});

    logger_.inf() << "Camera at: "<< camera_position.toString() << " rotation: " << camera_rotation.toString();

    Json::Value objectsNode;
    objectsNode = getOrDie(sceneNode, "objects");

    for(auto& object : objectsNode)
    {
        logger_.dbg() << "Object: "<< object.get("type","unknown").asString();
        auto objectType = object.get("type", "null").asString();

        switch(objectMapping[objectType])
        {
            case ObjectType::Sphere : loadSphere(scene, object); break;
            case ObjectType::Plane  : loadPlane(scene, object); break;
            case ObjectType::Light  : loadLight(scene, object); break;
            default : throw std::string("Unknown object type: ") + objectType;
        };
    }

    logger_.dbg() << "Loaded objects: " << scene.getObjects().size();
    logger_.dbg() << "Loaded lights: " << scene.getLights().size();    

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
    double x = position.get("x", 0.0).asDouble();
    double y = position.get("y", 0.0).asDouble();
    double z = position.get("z", 0.0).asDouble();
    return core::Point{x, y, z};    
}

core::Vector Loader::loadRotation(Json::Value& objectNode)
{
    Json::Value rotation = getOrDie(objectNode, "rotation");
    double x = rotation.get("x", 0.0).asDouble();
    double y = rotation.get("y", 0.0).asDouble();
    double z = rotation.get("z", 0.0).asDouble();
    return core::Vector{x, y, z};    
}

core::Vector Loader::loadFov(Json::Value& objectNode)
{
    Json::Value rotation = getOrDie(objectNode, "fov");
    double x = rotation.get("x", 0.0).asDouble();
    double y = rotation.get("y", 0.0).asDouble();
    return core::Vector{x, y, 0.0};    
}

core::Material Loader::loadMaterial(Json::Value& objectNode)
{
    Json::Value material = getOrDie(objectNode, "material");
    core::Color ambient = loadColor(material, "ambient");
    core::Color specular = loadColor(material, "specular");
    core::Color diffuse = loadColor(material, "diffuse");
    double refractionIndex = material.get("refractionIndex", 0.0).asDouble();
    double opacity = material.get("opacity", 0.0).asDouble();
    return core::Material{ambient, specular, diffuse, refractionIndex, opacity};
}

core::Color Loader::loadColor(Json::Value& objectNode, std::string colorName)
{
    Json::Value color = getOrDie(objectNode, colorName);
    double r = color.get("r", 0.0).asDouble();
    double g = color.get("g", 0.0).asDouble();
    double b = color.get("b", 0.0).asDouble(); 
    return core::Color{r, g, b};
}

void Loader::loadSphere(Scene& scene, Json::Value& objectNode)
{
    logger_.dbg()<< "Loading sphere...";
    Json::Value sphereNode = objectNode.get("config", "null");  
    shape::Sphere::Ptr object = std::make_shared<shape::Sphere>();
    core::Point pos = loadPosition(sphereNode);
    double radius = getOrDie(sphereNode, "radius").asDouble();
    core::Material material = loadMaterial(sphereNode);
    
    object->setPosition(pos);
    object->setRadius(radius);
    object->setMaterial(material);
    scene.addObject(object);
}

void Loader::loadPlane(Scene& scene, Json::Value& objectNode)
{
    logger_.dbg()<< "Loading plane...";
    Json::Value planeNode = objectNode.get("config", "null");  
    shape::Plane::Ptr object = std::make_shared<shape::Plane>();
    core::Point pos = loadPosition(planeNode);
    core::Material material = loadMaterial(planeNode);
    
    object->setPosition(pos);
    object->setMaterial(material);
    scene.addObject(object);
}

void Loader::loadLight(Scene& scene, Json::Value& objectNode)
{
    logger_.dbg()<< "Loading light...";
    Json::Value lightNode = objectNode.get("config", "null");
    shape::Light::Ptr object = std::make_shared<shape::Light>();
    core::Point pos = loadPosition(lightNode);
    core::Color color = loadColor(lightNode, "color");
    object->setPosition(pos);
    object->setColor(color);
    scene.addLight(object);
}


}  // namespace scene
}  // namespace rt