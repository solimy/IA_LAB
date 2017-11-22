#include <ctime>
#include <exception>
#include <iostream>
#include <string>
#include <random>

#include "Utils.h"
#include "Genetics.h"

class CTour : public Genetics::IChromosome {
	double m_fitness;
	Utils::matrix_t* m_matrix;

	CTour(CTour* p1, CTour* p2) {
		std::size_t const half_size = p1->m_path.path.size() / 2;

		m_path.path.assign(p1->m_path.path.begin(), p1->m_path.path.begin() + half_size);
		m_path.path.insert(m_path.path.end(), p2->m_path.path.begin() + half_size, p2->m_path.path.end());
		m_matrix = p1->m_matrix;
	}


public:
	Utils::Path m_path;

	CTour(Utils::matrix_t* matrix) {
		m_matrix = matrix;
		for (int i = 0, j = matrix->size(); i < j; ++i) m_path.path.push_back(i);
		m_path.path.push_back(0);
	}

	IChromosome* crossover(IChromosome* chromosome, double rate) {
		CTour* child = new CTour(this, (CTour*) chromosome);
		return child;
	}

	int mutate(double rate) {
		for (int i = 0, j = m_path.path.size(); i < j; ++i) if (std::rand() % 101 <= rate*100) m_path.path[i] = std::rand() % m_matrix->size();
		return 0; 
	}

	int evaluateFitness() {
		if (m_path.path.front() != 0 || m_path.path.back() != 0) {
			m_fitness = 0;
			return 0;
		}
		for (int i = 0, j = m_matrix->size(); i < j; ++i) if (std::find(m_path.path.begin(), m_path.path.end(), i) == m_path.path.end()) {
			m_fitness = 0;
			return 0;
		}
		Utils::path_calc(m_path, *m_matrix);
		m_fitness = 100 / m_path.length;
		return 0; 
	}

	double getFitness() { return m_fitness; }
};

class CTourFactory : public Genetics::IChromosomeFactory {
	Utils::matrix_t* m_matrix;
public:
	Genetics::IChromosome* newChromosome() const {
		return new CTour(m_matrix);
	}

	CTourFactory(Utils::matrix_t* matrix) {
		m_matrix = matrix;
		std::srand(std::time(0));
	}
};

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
		Genetics::CPopulation population(200, 0.01, 0.01, 20, 30);
		CTourFactory cfactory(matrix);
		CTour* best = NULL;

		population.initialize(cfactory);
		for (int i = 100; i > 0; --i) {
			population.evolveOnce();
			best = (CTour*)population.findBest();
		}
		Utils::path_dump(best->m_path);
		std::cout << "elapsed time:" << std::clock() << "ms" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	return 0;
}