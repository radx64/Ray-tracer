#include <iostream>

#include "core/Point.hpp"
#include "core/Vector.hpp"

int main(int argc, char** argv)
{
	std::cout << "Params given: " << argc << std::endl <<"To executable: "<< argv[0] << std::endl;

	rt::core::Point p(1.0, 2.0, 3.0);
	std::cout << p << std::endl;
	rt::core::Vector v(1.0, 2.0, 3.0);
	std::cout << v << std::endl;
	rt::core::Vector z = v + p;
	std::cout << z << std::endl;
}