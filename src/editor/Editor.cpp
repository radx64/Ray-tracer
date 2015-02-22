#include "Editor.hpp"

namespace rt
{
namespace editor
{
    double Editor::rotation_;
    std::vector<int> Editor::windowIds_;
    scene::Scene Editor::scene_;
    Raytracer::ImgType Editor::imageToDraw_;
}  // namespace editor
}  // namespace rt