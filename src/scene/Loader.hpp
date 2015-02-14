#ifndef RT_SCENE_LOADER_HPP_
#define RT_SCENE_LOADER_HPP_

#include <string>

#include "libs/jsoncpp/json/json.h"

#include "Loader.hpp"
#include "Scene.hpp"

namespace rt
{
namespace scene
{

class Loader
{
public:
	Loader()
	{ }

	Scene load(std::string filename);
	Json::Value getOrDie(Json::Value node, std::string name);
};

}  // namespace scene
}  // namespace rt

#endif  // RT_SCENE_LOADER_HPP_