// tsp_agent_2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <set>
#include <map>

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
		std::set<int> left_nodes; for (int i = 1, j = matrix->size(); i < j; ++i) left_nodes.insert(i);
		Utils::Path p;

		p.path.push_back(0);
		while (left_nodes.size() > 0) {
			std::map<int, int> distances;
			std::vector< int >& line = (*matrix)[p.path.back()];
			for (int i = 0, j = matrix->size(); i < j; ++i) distances[line[i]] = i;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
    return 0;
}

