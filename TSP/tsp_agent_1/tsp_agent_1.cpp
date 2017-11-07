// tsp_agent_1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <ctime>
#include <algorithm>
#include <future>
#include <thread>
#include <chrono>
#include <random>

#include "Utils.h"

struct Path
{
	std::vector<int> path;
	long length;
	void dump() { for (auto& val : path) std::cout << val << std::endl; }
};

Path* find_a_random_path(Utils::matrix_t const& matrix, unsigned seed) {
	Path* path = new Path();

	for (int i = 0, j = matrix.size(); i < j; ++i) path->path.push_back(i);
	std::shuffle(path->path.begin(), path->path.end(), std::default_random_engine(seed));
	return path;
}

int main(int ac, char** av)
{
	if (ac == 1)
	{
		std::cerr << "Error: usage: ./tsp_agent_1 matrix_file";
		return 1;
	}
	try
	{
		std::clock_t begin = std::clock();
		begin = std::clock() - begin;

		/*Matrix creation*/
		std::clock_t step_1 = std::clock();
		Utils::matrix_t* matrix = Utils::matrix_builder(av[1]);
		step_1 = std::clock() - step_1;

		/*Path finding*/
		std::clock_t step_2 = std::clock();
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::vector< std::packaged_task<Path*(Utils::matrix_t const&, unsigned)> > tasks;
		std::vector< std::future< Path* > > paths;
		std::vector< std::thread > threads;
		tasks.reserve(std::thread::hardware_concurrency());
		threads.reserve(std::thread::hardware_concurrency());
		for (int i = 0, j = std::thread::hardware_concurrency(); i < j; ++i) {
			tasks.emplace_back(find_a_random_path);
			paths.push_back(tasks.back().get_future());
			threads.emplace_back(std::move(tasks.back()), *matrix, std::clock()+i+seed);
		}
		for (auto& f : paths) {
			Path* p = f.get();
			delete p;
		}
		for (auto& t : threads) t.join();
		step_2 = std::clock() - step_2;

		/*program end*/
		std::clock_t end;
		end = std::clock();
		std::cout << "begin: " << begin << "ms" << std::endl;
		std::cout << "step_1: " << step_1 << "ms" << std::endl;
		std::cout << "step_2: " << step_2 << "ms" << std::endl;
		std::cout << "total: " << end << "ms" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
    return 0;
}

