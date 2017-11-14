#include <iostream>
#include <set>
#include <map>
#include <ctime>

#include "Utils.h"



int main(int ac, char** av)
{
	if (ac == 1)
	{
		std::cerr << "Error: usage: ./tsp_agent_2 matrix_file";
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
			for (int i = 0, j = matrix->size(); i < j; ++i)
				if (left_nodes.find(i) != left_nodes.end())
					distances[line[i]] = i;
			auto it = distances.begin();
			left_nodes.erase(it->second);
			p.length += it->first;
			p.path.push_back(it->second);
		}
		p.length += (*matrix)[p.path.front()][p.path.back()];
		p.path.push_back(0);
		Utils::path_dump(p);
		std::cout << "elapsed time:" << std::clock() << "ms" << std::endl;
		while (std::clock() < 5000) {
			static int iteration;
			for (int j = p.path.size() - 4; iteration < j; ++iteration) {
				int ia = p.path[iteration], ib = p.path[iteration+1], ic, id;
				for (int i = iteration + 2; i < j; ++i) {
					int length = p.length;
					ic = p.path[i];
					id = p.path[i+1];
					p.path[iteration+1] = ic;
					p.path[i] = ib;
					Utils::path_calc(p, *matrix);
					if (p.length > length) {
						p.path[iteration + 1] = ib;
						p.path[i] = ic;
						p.length = length;
					}
				}
			}
		}
		Utils::path_calc(p, *matrix);
		std::cout << p.length << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	return 0;
}
