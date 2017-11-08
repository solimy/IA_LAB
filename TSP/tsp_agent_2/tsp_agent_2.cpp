// tsp_agent_2.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "Utils.h"



int main(int ac, char** av)
{
	if (ac == 1)
	{
		std::cerr << "Error: usage: ./tsp_agent_1 matrix_file";
		return 1;
	}
	try
	{
		Utils::matrix_t* matrix = Utils::matrix_builder(av[1]);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
    return 0;
}

