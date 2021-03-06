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

#define TIMEOUT 25000

Utils::Path* find_a_random_path(Utils::matrix_t const& matrix, unsigned seed) {
	Utils::Path* path = new Utils::Path();

	for (int i = 1, j = matrix.size(); i < j; ++i) path->path.push_back(i);
	std::shuffle(path->path.begin(), path->path.end(), std::default_random_engine(seed));
	path->path.insert(path->path.begin(), 0);
	for (int i = 0, j = path->path.size() - 1; i < j; ++i) {
		path->length += matrix[path->path[i]][path->path[i+1]];
	}
	path->length += matrix[path->path.front()][path->path.back()];
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
		unsigned total_path_found = 0;
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		Utils::Path* best_path = find_a_random_path(*matrix, std::clock() + seed);
		std::vector< std::packaged_task<Utils::Path*(Utils::matrix_t const&, unsigned)> > tasks;
		std::vector< std::future< Utils::Path* > > paths;
		std::vector< std::thread > threads;
		tasks.reserve(std::thread::hardware_concurrency());
		threads.reserve(std::thread::hardware_concurrency());
		while (std::clock() < TIMEOUT) {
			for (int i = 0, j = std::thread::hardware_concurrency(); i < j; ++i) {
				tasks.emplace_back(find_a_random_path);
				paths.push_back(tasks.back().get_future());
				threads.emplace_back(std::move(tasks.back()), *matrix, std::clock() + i + seed);
			}
			for (auto& f : paths) {
				Utils::Path* p = f.get();
				if (p->length < best_path->length) {
					delete best_path;
					best_path = p;
				} else delete p;
			}
			for (auto& t : threads) t.join();
			total_path_found += std::thread::hardware_concurrency();
			threads.clear();
			tasks.clear();
			paths.clear();
		}
		best_path->path.push_back(0);
		step_2 = std::clock() - step_2;

		Utils::path_dump(*best_path);
		/*program end*/
		std::clock_t end;
		end = std::clock();
		//std::cout << "begin: " << begin << "ms" << std::endl;
		//std::cout << "step_1: " << step_1 << "ms" << std::endl;
		//std::cout << "step_2: " << step_2 << "ms" << std::endl;
		std::cout << "elapsed time: " << end << "ms" << std::endl;
		//std::cout << "Total number of paths found: " << total_path_found << std::endl;
		//std::cout << "Best path length: " << best_path->length << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
    return 0;
}

