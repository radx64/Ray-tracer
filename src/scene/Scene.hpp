#ifndef RT_SCENE_SCENE_HPP_
#define RT_SCENE_SCENE_HPP_

#include <vector>

#include "core/Object.hpp"

namespace rt
{
namespace scene
{

class Scene
{
public:
	Scene()
	{ }

private:
	std::vector<core::Object::Ptr> Objects_;
	//std::vector<core::Object::Ptr> Lights_;
};

}  // namespace scene
}  // namespace rt

#endif  // RT_SCENE_SCENE_HPP_