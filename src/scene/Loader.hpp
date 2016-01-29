#ifndef RT_SCENE_LOADER_HPP_
#define RT_SCENE_LOADER_HPP_

#include <string>

#include "libs/jsoncpp/json/json.h"
#include "libs/Logger.hpp"

#include "Scene.hpp"

namespace rt
{
namespace scene
{

class Loader
{
public:
    Loader() : logger_("Loader")
    { }

    Scene load(std::string filename);
   
private:
    Json::Value getOrDie(Json::Value node, std::string name);
    core::Point loadPosition(Json::Value& objectNode);
	void loadSphere(Scene& scene, Json::Value& sphereNode);
    void loadLight(Scene& scene, Json::Value& lightNode);
    Logger logger_;
};

}  // namespace scene
}  // namespace rt

#endif  // RT_SCENE_LOADER_HPP_