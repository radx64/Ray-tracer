#include <iostream>

#include "core/Point.hpp"
#include "core/Vector.hpp"

#include "editor/Editor.hpp"

void guiInterface(int argc, char** argv);
void textInterface();

int main(int argc, char** argv)
{
	std::cout << "Params given: " << argc << std::endl <<"To executable: "<< argv[0] << std::endl;

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
    rt::editor::Editor editor;
    editor.show(argc, argv);
}

void textInterface()
{
    rt::core::Point p(1.0, 2.0, 3.0);
    std::cout << p << std::endl;
    rt::core::Vector v(1.0, 2.0, 3.0);
    std::cout << v << std::endl;
    rt::core::Vector z = v + p;
    std::cout << z << std::endl;
}
