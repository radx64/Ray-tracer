#include <iostream>
#include <algorithm>
#include <stdint.h>
#include <png++/png.hpp>
#include <libs/Logger.hpp>

#include "Intro.hpp"
#include "Raytracer.hpp"
#include "core/Point.hpp"
#include "core/Vector.hpp"
#include "scene/Loader.hpp"
#include "scene/Scene.hpp"
#include "shape/Sphere.hpp"


void guiInterface(int argc, char** argv);
void textInterface();

Logger logger("Main");

int main(int argc, char** argv)
{
    logger.setLevel(LogLevel::DBG);
    printIntro();
    logger.inf() << "Params given: " << argc <<" to executable: "<< argv[0];
    if (argc > 1)
    {
        logger.inf() << "Starting graphical interface using OpenGL...";
        guiInterface(argc, argv);
    }
    else
    {
        logger.inf() << "Starting text interface...";
        textInterface();
    }
    return 0;
}

void guiInterface(int argc, char** argv)
{
    logger.err() << "NOT IMPLEMENTED YET!. USE TEXT INTERFACE.";
}

void textInterface()
{
    try
    {
        rt::scene::Loader loader;
        rt::scene::Scene s = loader.load("../scene.json");
        logger.inf() << "Scene loaded";
        rt::Raytracer raytracer;
        logger.inf() << "Raytracer created";
        raytracer.load(s);
        raytracer.run();
        logger.inf() << "Raytracer finished";       
        rt::Raytracer::Image image;
        image = raytracer.getImage();

        png::image<png::rgb_pixel> pngImage(IMG_SIDE, IMG_SIDE);
        for (size_t y = 0; y < pngImage.get_height(); ++y)
        {
            for (size_t x = 0; x < pngImage.get_width(); ++x)
            {
                pngImage[pngImage.get_height()-y-1][x] = png::rgb_pixel(
                    image[x][y].red,
                    image[x][y].green,
                    image[x][y].blue);
            }
        }
        
        pngImage.write("../render.png");

    }
    catch(const std::string& e)
    {
        logger.err() << "Exception was thrown: " << "\n" << "\t"<< e;
    }
}
