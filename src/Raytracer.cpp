#include "Raytracer.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <thread>

constexpr bool REFRACTIONS_ENABLED = true;
constexpr bool DEPTHMAP_ENABLED = false;
constexpr bool SHADOWS_ENABLED = true;
constexpr bool SHADOWS_DEBUG = false;
constexpr double MAX_DEPTH = 100000.0;
constexpr int maxReccursionLimit = 3;

constexpr bool MULTITHREAD_MODE = true;
constexpr int IMG_WIDTH = 640;
constexpr int IMG_HEIGHT = 480;

namespace rt {

struct ThreadInfo {
  unsigned int index;
  unsigned int progress;
  unsigned int finished;
};

std::tuple<const unsigned int, const unsigned int> Raytracer::getImageSize() {
  return std::tuple(IMG_HEIGHT, IMG_WIDTH);
}

Raytracer::Raytracer() : logger_("Raytracer") {
  buffer_.resize(IMG_WIDTH);
  for (int i = 0; i < IMG_WIDTH; ++i) {
    buffer_[i].resize(IMG_HEIGHT);
  }
}

core::Color clamp(core::Color c) {
  /* need to implement some exponential color clamping or something*/

  if (c.red > 255)
    c.red = 255;
  if (c.green > 255)
    c.green = 255;
  if (c.blue > 255)
    c.blue = 255;

  if (c.red < 0)
    c.red = 0;
  if (c.green < 0)
    c.green = 0;
  if (c.blue < 0)
    c.blue = 0;

  return c;
}

core::Color depthMap(const double distance, const double maxDepth) {
  double d = (distance / maxDepth) * 255;
  return core::Color(255 - d, 255 - d, 255 - d);
}

Raytracer::Image Raytracer::getImage() { return buffer_; }

void Raytracer::load(scene::Scene &s) { scene_ = s; }

void print_threads_progress(std::vector<rt::ThreadInfo> *thread_info) {
  for (const auto &thread : *thread_info) {
    std::cout << "[" << thread.index << "] " << thread.progress << "%    ";
  }
  std::cout << "\r";
  std::flush(std::cout);
}

void Raytracer::progress_check(std::vector<rt::ThreadInfo> *thread_info) {

  while (std::any_of(thread_info->begin(), thread_info->end(),
                     [](const auto ti) { return ti.finished == false; })) {
    print_threads_progress(thread_info);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  };
  print_threads_progress(thread_info);
  std::cout << std::endl;
  return;
}

void Raytracer::run() {
  unsigned int threads_count{1};

  if (MULTITHREAD_MODE) {
    threads_count = std::thread::hardware_concurrency();
    logger_.dbg() << "Hardware supports " << threads_count << " threads";
    logger_.dbg() << "Resolution " << IMG_WIDTH << "x" << IMG_HEIGHT;
    logger_.dbg() << "Single thread should render " << IMG_WIDTH << "x"
                  << IMG_HEIGHT / threads_count;
  }

  std::vector<std::thread> thread_pool;
  std::vector<rt::ThreadInfo> thread_info;
  thread_info.reserve(threads_count);

  for (unsigned int t_id = 0; t_id < threads_count; ++t_id) {
    logger_.dbg() << "Spawning thread " << t_id;
    unsigned int strip_size = IMG_HEIGHT / threads_count;
    int strip_y1 = -IMG_HEIGHT / 2 + t_id * strip_size;
    int strip_y2 = -IMG_HEIGHT / 2 + t_id * strip_size + strip_size;

    thread_info.emplace_back(rt::ThreadInfo{t_id, 0, false});
    thread_pool.emplace_back(std::thread(&Raytracer::render, this, strip_y1,
                                         strip_y2, &thread_info[t_id]));
  }

  std::thread progress_thread(&Raytracer::progress_check, this, &thread_info);

  for (auto &thread : thread_pool) {
    thread.join();
  }
  progress_thread.join();
}

void Raytracer::render(const int min_y, const int max_y,
                       rt::ThreadInfo *thread_info) {
  const auto camera_fov = scene_.getCamera().fov_;
  double fovx = camera_fov.x() * (M_PI / 180.0);
  double fovy = camera_fov.y() * (M_PI / 180.0);

  for (int height = min_y; height < max_y; height++) {
    for (int width = -IMG_WIDTH / 2; width < IMG_WIDTH / 2; width++) {
      const auto camera_position = scene_.getCamera().position_;

      core::Point origin(camera_position.x() + width,
                         camera_position.y() + height,
                         camera_position.z() + 0.0);

      double hd = (float)height / (IMG_HEIGHT);
      double wd = (float)width / (IMG_WIDTH);

      core::Vector direction((wd)*tan(fovx / 2), (hd)*tan(fovy / 2), 1.0);
      direction.normalize();

      core::Ray viewRay(origin, direction);

      core::Color c = trace(viewRay, 0);

      buffer_[width + IMG_WIDTH / 2][height + IMG_HEIGHT / 2] = clamp(c);
    }
    thread_info->progress = (height - min_y) * 100 / (max_y - min_y);
  }
  thread_info->finished = true;
}

core::Color Raytracer::trace(core::Ray &ray, int reccursionStep) {
  core::Color local = {0.0, 0.0, 0.0};

  if (reccursionStep > maxReccursionLimit)
    return local;

  double distance = MAX_DEPTH;

  auto objects = scene_.getObjects();

  core::Object::Ptr closestObject = nullptr;

  for (auto &object : objects) {
    if (object->hit(ray, distance))
      closestObject = object;
  };

  if (DEPTHMAP_ENABLED) {
    local = depthMap(distance, 500.0);
  } else {
    if (closestObject == nullptr)
      return core::Color{30.0, 30.0, 30.0};

    core::Point collision = ray.getOrigin() + ray.getDirection() * distance;
    core::Vector normal = closestObject->getNormalAt(collision);

    core::Material closestObjectMaterial =
        closestObject->getMaterialAt(collision);
    core::Vector closestObjectUV = closestObject->UV(collision);

    // checkered pattern fo UV map testing
    bool checkered = false;
    float sines = cos(M_PI * 40 * closestObjectUV.x()) *
                  cos(M_PI * 40.0 * closestObjectUV.y());
    if (sines < 0)
      checkered = true;
    auto lights = scene_.getLights();
    for (auto &light : lights) {

      // PHONG lighting model
      double a = 0.7;
      double b = 0.01;
      double c = 0.001;

      core::Vector V = ray.getDirection(); // observation vector
      V.normalize();
      core::Vector L =
          light->getPosition() - collision; // light incidence vector
      double t2 = sqrtf(L.dot(L));
      core::Vector lightDirection = L * (2.0f / t2);
      L.normalize(); // do not normalize L before light direction calculatuions
      lightDirection.normalize();
      core::Ray lightRay(collision, lightDirection);

      bool isInShadow = false;
      core::Object::Ptr castingShadowObject{nullptr};

      if (SHADOWS_ENABLED) {
        for (auto &object : objects) {
          if (object->isCastingShadow && object->hit(lightRay, t2)) {
            isInShadow = true;
            castingShadowObject = object;
            break;
          }
        };
      }

      double dotNL = normal.dot(L);

      core::Vector R = L - (normal * dotNL * 2.0); // reflected vector
      R.normalize();

      double dotVR =
          V.dot(R); // angle betwen observation vector and reflected vector

      if (dotVR < 0)
        dotVR = 0;

      core::Vector difference = light->getPosition() - collision;

      double di = sqrtf(difference.x() * difference.x() +
                        difference.y() * difference.y() +
                        difference.z() * difference.z());

      double lightning_factor = 1.0 / (a + b * di + c * di * di);

      double casting_shadow_opacity_factor = 1.0;
      if (isInShadow) {
        casting_shadow_opacity_factor =
            castingShadowObject->getMaterial().opacity;
      }

      if (SHADOWS_DEBUG && isInShadow)
        local = core::Color{255.0, 0.0, 255.0};
      else {
        core::Color ambient = closestObjectMaterial.ambient * lightning_factor *
                              casting_shadow_opacity_factor;
        core::Color diffuse = closestObjectMaterial.diffuse *
                              light->getColor() * dotNL * lightning_factor *
                              10.0 * casting_shadow_opacity_factor;
        core::Color specular = closestObjectMaterial.specular *
                               light->getColor() * pow(dotVR, 40) * 0.95 *
                               casting_shadow_opacity_factor;

        if (checkered) {
          diffuse = diffuse * 2.0;
        }

        local = local + clamp(ambient) + clamp(diffuse) + clamp(specular);
      }
    }

    core::Ray reflected(collision,
                        ray.getDirection() -
                            normal * (ray.getDirection().dot(normal)) * 2.0);
    core::Color reflectedColor = trace(reflected, reccursionStep + 1);
    local = local +
            clamp(reflectedColor * 0.3); // todo: reflection factor as paramter

    if (closestObjectMaterial.opacity > 0.0 &&
        REFRACTIONS_ENABLED) // comparing doubles should use some kind of
                             // epsilon (std::numeric_limis<double> maybe?)
    {
      double n1;
      double n2;
      double cosI = ray.getDirection().dot(normal);

      if (cosI > 0) {
        n1 = closestObjectMaterial.refractionIndex;
        n2 = 1.0f;
      } else {
        n1 = 1.0f;
        n2 = closestObjectMaterial.refractionIndex;
        cosI = -cosI;
      }

      double cosT = 1.0f - pow(n1 / n2, 2.0f) * (1.0f - pow(cosI, 2.0f));

      if (cosT < 0.0f) {
        // This is total internal reflection (but i'm lazy so it still
        // refracting) todo: fix me
        core::Ray refraction(collision, ray.getDirection() * (n1 / n2) +
                                            normal * ((n1 / n2) * cosI - cosT));

        core::Color refractionColor = trace(refraction, reccursionStep + 1);
        local = local + clamp(refractionColor * closestObjectMaterial.opacity);

      } else {
        core::Ray refraction(collision, ray.getDirection() * (n1 / n2) +
                                            normal * ((n1 / n2) * cosI - cosT));

        core::Color refractionColor = trace(refraction, reccursionStep + 1);
        local = local + clamp(refractionColor * closestObjectMaterial.opacity);
      }
    }
  }
  return local;
}

} // namespace rt