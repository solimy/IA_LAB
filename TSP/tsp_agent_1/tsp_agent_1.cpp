// tsp_agent_1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <ctime>

#include "Utils.h"

int main(int ac, char** av)
{
	if (ac == 1) {
		std::cerr << "Error: usage: ./tsp_agent_1 matrix_file";
		return 1;
	}
	try {
		std::clock_t begin = std::clock();
		auto testV = Utils::matrix_builder(av[1]);
		std::clock_t step_1 = std::clock();
		std::clock_t end = std::clock();
		std::cout << "begin: " << begin << "ms" << std::endl;
		std::cout << "step_1: " << std::clock_t(step_1 - begin) << "ms" << std::endl;
		std::cout << "total: " << end << "ms" << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}
    return 0;
}

