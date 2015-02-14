#ifndef RT_SCENE_SCENE_HPP_
#define RT_SCENE_SCENE_HPP_

#include <vector>
#include <string>

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
    void addObject(core::Object::Ptr object);

    void setName(std::string name);
    std::string getName();

private:
    std::vector<core::Object::Ptr> Objects_;
    //std::vector<core::Object::Ptr> Lights_;
    std::string name_;
};

}  // namespace scene
}  // namespace rt

#endif  // RT_SCENE_SCENE_HPP_