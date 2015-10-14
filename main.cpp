#include <iostream>

#include "Intro.hpp"
#include "core/Point.hpp"
#include "core/Vector.hpp"
#include "editor/Editor.hpp"
#include "scene/Loader.hpp"
#include "scene/Scene.hpp"
#include "shape/Sphere.hpp"


void guiInterface(int argc, char** argv);
void textInterface();

int main(int argc, char** argv)
{
    std::cout << "Params given: " << argc << std::endl <<"To executable: "<< argv[0] << std::endl;
    printIntro();
    if (argc > 1)
    {
        std::cout << "Starting GUI interface using OpenGL..." << std::endl;
        guiInterface(argc, argv);
    }
    else
    {
        std::cout << "Starting text interface..." << std::endl;
        textInterface();
    }
    return 0;
}

void guiInterface(int argc, char** argv)
{
    try
    {
        rt::scene::Loader loader;
        rt::scene::Scene s = loader.load("../scene.json");
        rt::Raytracer raytracer;
        raytracer.load(s);
        raytracer.run();
        rt::Raytracer::ImgType image;
        image = raytracer.getImage();

        rt::editor::Editor editor;
        editor.show(argc, argv, s, image);
    }
    catch(std::string str)
    {
        std::cout << "Exception was thrown: " << str << std::endl;
    }
}

void textInterface()
{
    rt::core::Point p(1.0, 2.0, 3.0);
    std::cout << p << std::endl;
    rt::core::Vector v(1.0, 2.0, 3.0);
    std::cout << v << std::endl;
    rt::shape::Sphere s();
    rt::core::Vector z = v + p;
    std::cout << z << std::endl;
}
