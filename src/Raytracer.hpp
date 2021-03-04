#ifndef RT_RAYTRACER
#define RT_RAYTRACER

#include <tuple>
#include <vector>

#include <libs/Logger.hpp>

#include "core/Color.hpp"
#include "scene/Scene.hpp"

namespace rt {

struct ThreadInfo;

class Raytracer {
public:
  using Image = std::vector<std::vector<core::Color>>;
  Raytracer();

  void load(scene::Scene &s);
  void run();
  Image getImage() const;
  std::tuple<const unsigned int, const unsigned int> getImageSize() const;

private:
  void render(const int min_y, const int max_y, rt::ThreadInfo *thread_info);
  core::Color trace(core::Ray &ray, int reccursionStep);
  void progress_check(std::vector<rt::ThreadInfo> *thread_info);

  Image buffer_;
  scene::Scene scene_;

  Logger logger_;
};

} // namespace rt

#endif // RT_RAYTRACER