#include <ctime>
#include <exception>
#include <iostream>

#include "Utils.h"
#include "Genetics.h"

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
		Genetics::Default::ChromosomeFactory< Genetics::Default::Chromosome<int> > cfactory;
		Genetics::CPopulation population(20, 0.3, 0.3);

		population.initialize(cfactory);
		population.evaluateFitness();
		std::cout << "elapsed time:" << std::clock() << "ms" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	return 0;
}