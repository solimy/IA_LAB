#include <ctime>
#include <exception>
#include <iostream>

#include "Utils.h"

int main(int ac, char** av)
{
	if (ac == 1)
	{
		std::cerr << "Error: usage: ./tsp_agent_3 matrix_file";
		return 1;
	}
	try
	{
		Utils::matrix_t* matrix = Utils::matrix_builder(av[1]);
		Utils::Path p;
		Utils::path_dump(p);
		std::cout << "elapsed time:" << std::clock() << "ms" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	return 0;
}