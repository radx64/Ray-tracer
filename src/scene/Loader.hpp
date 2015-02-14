#ifndef RT_SCENE_LOADER_HPP_
#define RT_SCENE_LOADER_HPP_

#include <string>

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
};

}  // namespace scene
}  // namespace rt

#endif  // RT_SCENE_LOADER_HPP_