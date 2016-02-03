#ifndef RT_SCENE_LOADER_HPP_
#define RT_SCENE_LOADER_HPP_

#include <string>
#include <unordered_map>

#include "libs/jsoncpp/json/json.h"
#include "libs/Logger.hpp"

#include "core/Material.hpp"

#include "Scene.hpp"

namespace rt
{
namespace scene
{

enum class ObjectType
{
    Sphere,
    Light
};

class Loader
{
public:
    Loader();

    Scene load(std::string filename);
   
private:
    Json::Value getOrDie(Json::Value node, std::string name);
    core::Point loadPosition(Json::Value& objectNode);
    core::Material loadMaterial(Json::Value& objectNode);
    core::Color loadColor(Json::Value& objectNode, std::string colorName);
	void loadSphere(Scene& scene, Json::Value& sphereNode);
    void loadLight(Scene& scene, Json::Value& lightNode);


    Logger logger_;
    std::unordered_map<std::string, ObjectType> objectMapping;
};

}  // namespace scene
}  // namespace rt

#endif  // RT_SCENE_LOADER_HPP_