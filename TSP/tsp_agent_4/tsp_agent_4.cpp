#include <ctime>
#include <exception>
#include <iostream>
#include <string>
#include <random>

#include "Utils.h"
#include "Genetics.h"

class CDNA : public Genetics::IChromosome {
public:
	std::string* m_target;
	std::string m_dna;
	double m_fitness;

	CDNA(std::string* target) { 
		m_target = target;
		for (int i = 0, j = target->size(); i < j; ++i) m_dna += ('a' + std::rand() % 26);
	}

	IChromosome* crossover(IChromosome* chromosome, double rate) {
		CDNA* parent = (CDNA*)chromosome;
		CDNA* child = new CDNA(m_target);
		child->m_dna = m_dna;
		for (int i = parent->m_dna.size() / 2, j = parent->m_dna.size(); i < j; ++i)
			child->m_dna[i] = parent->m_dna[i];
		return child;
	}

	int mutate(double rate) { 
		for (int i = 0, j = m_dna.size(); i < j; ++i) if (std::rand() % 101 <= rate*100) m_dna[i] = ('a' + std::rand() % 26);
		return 0; 
	}

	int evaluateFitness() {
		m_fitness = 0;

		for (int i = 0, j = m_dna.size(); i < j; ++i) if (m_dna[i] == (*m_target)[i]) ++m_fitness;
		return 0; 
	}

	double getFitness() { return m_fitness; }
};

class CDNAFactory : public Genetics::IChromosomeFactory {
	std::string* m_target;
public:
	Genetics::IChromosome* newChromosome() const {
		return new CDNA(m_target);
	}

	CDNAFactory(std::string* target) { 
		m_target = target; 
		std::srand(std::time(0));
	}
};

int main(int ac, char** av)
{
	if (ac == 0)
	{
		std::cerr << "Error: usage: ./tsp_agent_3 matrix_file";
		return 1;
	}
	try
	{
		std::string target("tobeornottobe");
		//Utils::matrix_t* matrix = Utils::matrix_builder(av[1]);
		Genetics::CPopulation population(200, 0.01, 0.01, 20, 30);
		CDNAFactory cfactory(&target);

		population.initialize(cfactory);
		for (int i = 1000; i > 0; --i) {
			population.evolveOnce();
			CDNA* best = (CDNA*)population.findBest();
			std::cout << "Generation " << 1000 - i << ":" << best->m_dna << " " << best->getFitness() << std::endl;
			if (best->m_dna.compare(target) == 0) break;
		}
		std::cout << "elapsed time:" << std::clock() << "ms" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	return 0;
}