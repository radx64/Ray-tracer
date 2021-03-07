#include "Raytracer.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <thread>
#include <random>

constexpr bool REFRACTIONS_ENABLED = true;
constexpr bool DEPTHMAP_ENABLED = false;
constexpr bool SHADOWS_ENABLED = true;
constexpr bool SHADOWS_DEBUG = false;
constexpr double MAX_DEPTH = 100000.0;
constexpr unsigned int MAX_RECCURSION_LIMIT = 3;

constexpr bool SPHERICAL_LIGHTS_MODEL = true;
constexpr unsigned int LIGHT_PROBES_COUNT = 16;
constexpr unsigned int LIGHT_RADIUS = 50;

constexpr bool MULTITHREAD_MODE = true;
constexpr int IMG_WIDTH = 800;
constexpr int IMG_HEIGHT = 600;

namespace rt {

int get_random_value(unsigned int max)
{
  static std::random_device r;
  static std::mt19937 engine(r());
  static std::uniform_int_distribution<int> uniform_dist(-max, max);
  return uniform_dist(engine);  
}

struct ThreadInfo {
  unsigned int index;
  unsigned int progress;
  unsigned int finished;
};

std::tuple<const unsigned int, const unsigned int> Raytracer::getImageSize() const
{
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

Raytracer::Image Raytracer::getImage() const{ return buffer_; }

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

  if (reccursionStep > MAX_RECCURSION_LIMIT)
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
      return core::Color{30.0, 30.0, 30.0}; //this should be some background defined color (or transparency channel)

    core::Point collision = ray.getOrigin() + ray.getDirection() * distance;
    core::Vector normal = closestObject->getNormalAt(collision);

    const core::Material& closestObjectMaterial =
        closestObject->getMaterialAt(collision);
    core::Vector closestObjectUV = closestObject->UV(collision);
    auto lights = scene_.getLights();
    unsigned int light_probes_count = LIGHT_PROBES_COUNT;
    if (!SPHERICAL_LIGHTS_MODEL) light_probes_count = 1;

    for (auto &scene_light : lights) {


      for (unsigned int light_probe_index = 0; light_probe_index < light_probes_count; ++ light_probe_index)
      {
        const double random_x = get_random_value(LIGHT_RADIUS);
        const double random_y = get_random_value(LIGHT_RADIUS);
        const double random_z = get_random_value(LIGHT_RADIUS);

        rt::core::Point light_position = scene_light->getPosition();
        rt::core::Point light_delta_point(random_x, random_y,random_z);
        light_position = light_position + light_delta_point;

        // PHONG shading model
        double a = 0.7;
        double b = 0.01;
        double c = 0.001;

        core::Vector V = ray.getDirection(); // observation vector
        V.normalize();
        core::Vector L =
            light_position - collision; // light incidence vector
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

        core::Vector difference = light_position - collision;

        double di = sqrtf(difference.x() * difference.x() +
                          difference.y() * difference.y() +
                          difference.z() * difference.z());

        double lightning_factor = 1.0 / (a + b * di + c * di * di);

        double casting_shadow_opacity_factor = 1.0;
        if (isInShadow) {
          casting_shadow_opacity_factor =
              castingShadowObject->getMaterial().get_opacity_at_uv(closestObjectUV.x(), closestObjectUV.y());
        }

        if (SHADOWS_DEBUG && isInShadow)
          local = core::Color{255.0, 0.0, 255.0};
        else {
          
          core::Color ambient = closestObjectMaterial.get_ambient_at_uv(closestObjectUV.x(), closestObjectUV.y()) * 
                                lightning_factor * casting_shadow_opacity_factor;
          core::Color diffuse = closestObjectMaterial.get_diffuse_at_uv(closestObjectUV.x(), closestObjectUV.y()) *
                                scene_light->getColor() * dotNL * lightning_factor *
                                20.0 * casting_shadow_opacity_factor;
          core::Color specular = closestObjectMaterial.get_specular_at_uv(closestObjectUV.x(), closestObjectUV.y()) *
                                scene_light->getColor() * pow(dotVR, 40) * 0.95 *
                                casting_shadow_opacity_factor;
          local = local + (clamp(ambient) + clamp(diffuse) + clamp(specular)) * (1.0 / (double)light_probes_count);
        }
      }
    }

    core::Ray reflected(collision,
                        ray.getDirection() -
                            normal * (ray.getDirection().dot(normal)) * 2.0);
    core::Color reflectedColor = trace(reflected, reccursionStep + 1);
    local = local +
            clamp(reflectedColor * 0.3); // todo: reflection factor as paramter

    if (closestObjectMaterial.get_opacity_at_uv(closestObjectUV.x(), closestObjectUV.y()) > 0.0 &&
        REFRACTIONS_ENABLED) // comparing doubles should use some kind of
                            // epsilon (std::numeric_limis<double> maybe?)
    {
      double n1;
      double n2;
      double cosI = ray.getDirection().dot(normal);

      double local_refraction_index = closestObjectMaterial.get_refraction_index_at_uv(closestObjectUV.x(), closestObjectUV.y());

      if (cosI > 0) {
        n1 = local_refraction_index;
        n2 = 1.0f;
      } else {
        n1 = 1.0f;
        n2 = local_refraction_index;
        cosI = -cosI;
      }

      double cosT = 1.0f - pow(n1 / n2, 2.0f) * (1.0f - pow(cosI, 2.0f));

      double local_opacity_index = closestObjectMaterial.get_opacity_at_uv(closestObjectUV.x(), closestObjectUV.y());

      core::Ray refraction(core::Point(0.0,0.0,0.0), core::Vector(0.0,0.0,0.0));

      if (cosT < 0.0f) {
        // This is total internal reflection (but i'm lazy so it still
        // refracting) todo: fix me
        refraction = core::Ray(collision, ray.getDirection() * (n1 / n2) +
                                            normal * ((n1 / n2) * cosI - cosT));
      } else {
        refraction = core::Ray(collision, ray.getDirection() * (n1 / n2) +
                                            normal * ((n1 / n2) * cosI - cosT));
      }
        core::Color refractionColor = trace(refraction, reccursionStep + 1);
        local = local + clamp(refractionColor * local_opacity_index); 
    }
  }
  return local;
}

} // namespace rt