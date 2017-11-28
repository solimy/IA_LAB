#include <ctime>
#include <exception>
#include <iostream>
#include <string>
#include <random>
#include <set>
#include <map>

#include "Utils.h"
#include "Genetics.h"

class CTour : public Genetics::IChromosome {
	double m_fitness;
	Utils::matrix_t* m_matrix;

	CTour(CTour* p1, CTour* p2) {
		std::size_t const half_size = p1->m_path.path.size() / 2;

		m_path.path.assign(p1->m_path.path.begin(), p1->m_path.path.begin() + half_size);
		m_path.path.insert(m_path.path.end(), p1->m_path.path.begin() + half_size, p1->m_path.path.end());
		m_matrix = p1->m_matrix;
	}


public:
	Utils::Path m_path;

	CTour(Utils::matrix_t* matrix, Utils::Path* basePath) {
		m_matrix = matrix;
		m_path = *basePath;
	}

	IChromosome* crossover(IChromosome* chromosome, double rate) {
		CTour* child = new CTour(this, (CTour*) chromosome);
		return child;
	}

	int mutate(double rate) {
		int tmp;
		int jump;

		for (int i = 1, j = m_path.path.size() - 1; i < j; ++i) if (std::rand() % 101 <= rate * 100) {
			jump = (i + (std::rand() % j)) % (j+1);
			if (jump == 0 || jump >= j-1) jump = 1;
			tmp = m_path.path[jump];
			m_path.path[jump] = m_path.path[i];
			m_path.path[i] = tmp;
		}
		return 0;
	}

	int evaluateFitness() {
		Utils::path_calc(m_path, *m_matrix);
		m_fitness = 100 / m_path.length;
		return 0; 
	}

	double getFitness() { return m_fitness; }
};

class CTourFactory : public Genetics::IChromosomeFactory {
	Utils::matrix_t* m_matrix;
	Utils::Path* m_basePath;

public:
	Genetics::IChromosome* newChromosome() const {
		return new CTour(m_matrix, m_basePath);
	}

	CTourFactory(Utils::matrix_t* matrix, Utils::Path* basePath) {
		m_matrix = matrix;
		m_basePath = basePath;
		std::srand(std::time(0));
	}
};

int main(int ac, char** av)
{
	if (ac == 1)
	{
		std::cerr << "Error: usage: ./tsp_agent_4 matrix_file";
		return 1;
	}
	try
	{
		Utils::matrix_t* matrix = Utils::matrix_builder(av[1]);
		Utils::Path* basePath = Utils::TSP::greedy(matrix);
		basePath = Utils::TSP::two_opt(basePath, matrix);
		basePath = Utils::TSP::two_opt(basePath, matrix);
		basePath = Utils::TSP::two_opt(basePath, matrix);
		Genetics::CPopulation population(200, 0.01, 0.05, 100, 200);
		CTourFactory cfactory(matrix, basePath);
		CTour* best = NULL; best = new CTour(matrix, basePath);

		population.initialize(cfactory);
		for (int i = 0; i > 0; --i) {
			population.evolveOnce();
			best = (CTour*)population.findBest();
		}
		std::cout << Utils::path_isValid(best->m_path, *matrix) << std::endl;
		Utils::path_dump(best->m_path);
		std::cout << "elapsed time:" << std::clock() << "ms" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	return 0;
}
