#include <iostream>
#include <set>
#include <map>
#include <ctime>

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
		Utils::Path* p = Utils::Algorithm::greedy(matrix);
		int length;
		while (std::clock() < 25000) {
			length = p->length;
			p = Utils::Algorithm::two_opt(p, matrix);
			if (p->length == length) break;
		}
		Utils::path_dump(*p);
		std::cout << "elapsed time:" << std::clock() << "ms" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	return 0;
}
