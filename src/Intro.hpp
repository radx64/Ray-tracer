#include "libs/Color.hpp"

#include "Version.hpp"

static void printIntro()
{

terminal::Color lightRed(terminal::FG_LIGHT_RED);
terminal::Color red(terminal::FG_RED);
terminal::Color green(terminal::FG_GREEN);
terminal::Color white(terminal::FG_WHITE);
terminal::Color def(terminal::FG_DEFAULT);


std::cout << green << "+---------------------------+" << def << std::endl;
std::cout << green << "| "<<red <<"RayTracer " << green << "version " << white << VERSION << green << " |"<< def << std::endl;
std::cout << green << "+---------------------------+" << def << std::endl;    
std::cout << lightRed << "     █" << white << "█" << lightRed << "███      " << std::endl;
std::cout << lightRed << "    █" << white << "███" << lightRed << "███      " << std::endl;
std::cout << lightRed << "   █" << white << "█" << lightRed << "███████      " << std::endl;
std::cout << lightRed << "   ████████" << red << "█      " << std::endl;
std::cout << lightRed << "    █████" << red << "██      " << std::endl;
std::cout << lightRed << "     ██" << red << "███      " << std::endl;

};