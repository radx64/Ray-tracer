#include <algorithm>
#include <chrono>
#include <iostream>
#include <libs/Logger.hpp>
#include <png++/png.hpp>
#include <stdint.h>

#include "Intro.hpp"
#include "Raytracer.hpp"
#include "core/Point.hpp"
#include "core/Vector.hpp"
#include "scene/Loader.hpp"
#include "scene/Scene.hpp"
#include "shape/Sphere.hpp"

void textInterface();

Logger logger("Main");

int main(int argc, char **argv) {
  logger.setLevel(LogLevel::DBG);
  printIntro();
  logger.inf() << argc << " parameters passed to executable: " << argv[0];
  textInterface();
  return 0;
}

void saveImage(const rt::Raytracer& rt, const std::string& filename)
{
rt::Raytracer::Image image;
    image = rt.getImage();

    const auto image_size = rt.getImageSize();
    png::image<png::rgb_pixel> pngImage(std::get<1>(image_size),
                                        std::get<0>(image_size));
    for (size_t y = 0; y < pngImage.get_height(); ++y) {
      for (size_t x = 0; x < pngImage.get_width(); ++x) {
        pngImage[pngImage.get_height() - y - 1][x] = png::rgb_pixel(
            image[x][y].red, image[x][y].green, image[x][y].blue);
      }
    }

    pngImage.write(filename);
}


void raytrace(const std::string& scene_filename, const std::string& result_filename)
{
    rt::scene::Loader loader;
    rt::scene::Scene s = loader.load(scene_filename);
    logger.inf() << "Scene loaded";
    rt::Raytracer raytracer;
    logger.inf() << "Raytracer created";
    raytracer.load(s);

    auto start = std::chrono::system_clock::now();
    raytracer.run();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    logger.inf() << "Took " << std::setw(4) << diff.count() << " [s] to render " << scene_filename;
    logger.inf() << "Raytracer finished";
    saveImage(raytracer, result_filename);
}

void textInterface() {
  try {
    raytrace("../planets.json", "../planets.png");
    raytrace("../scene.json", "../render.png");

  } catch (const std::string &e) {
    logger.err() << "Exception was thrown: \n"
                 << "\t" << e;
  }
}
