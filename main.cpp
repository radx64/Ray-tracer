#include "core/Object.hpp"
#include <iostream>


int main(int argc, char** argv)
{
	std::cout << "Params given: " << argc << std::endl <<"To executable: "<< argv[0] << std::endl;
	Object o;
	o.doNothing();
}