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
    std::cout << "NOT IMPLEMENTED YET!. USE TEXT INTERFACE." << std::endl;
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

        png::image<png::rgb_pixel> pngImage(512, 512);
        for (size_t y = 0; y < pngImage.get_height(); ++y)
        {
            for (size_t x = 0; x < pngImage.get_width(); ++x)
            {
                
                if(image[x][y].red > 10000)
                {
                    pngImage[pngImage.get_height()-y-1][x] = png::rgb_pixel(100, 100, 100); 
                }

                else if(image[x][y].red > 20)
                {
                    pngImage[pngImage.get_height()-y-1][x] = png::rgb_pixel(255, 0, 0); 
                }
                else if (image[x][y].red > 15)
                {
                    pngImage[pngImage.get_height()-y-1][x] = png::rgb_pixel(0, 255, 0); 
                }
                else if (image[x][y].red > 10)
                {
                    pngImage[pngImage.get_height()-y-1][x] = png::rgb_pixel(0, 0, 255); 
                }
                else if (image[x][y].red > 5)
                {
                    pngImage[pngImage.get_height()-y-1][x] = png::rgb_pixel(0, 255, 255); 
                }
                else
                {
                    double d = image[x][y].red * 79;
                    char depth = std::min(char(d), char(255));
                    pngImage[pngImage.get_height()-y-1][x] = png::rgb_pixel(depth, depth, depth);
                }
                if (image[x][y].red < 0)
                {
                    pngImage[pngImage.get_height()-y-1][x] = png::rgb_pixel(100, 100, 0); 
                }

                if ((x == 256-80) && (y == 256))
                {
                    logger.dbg() << "Probing:" << (unsigned int)(image[x][y]).red;
                }
            }
        }
        
        pngImage.write("../render.png");

    }
    catch(std::string str)
    {
        std::cout << "Exception was thrown: " << str << std::endl;
    }
}
