#include "Genetics.h"

Genetics::CPopulation::CPopulation(int size, double crossover_probability, double mutation_probability) {
	m_size = size;
	m_pc = crossover_probability;
	m_pm = mutation_probability;
}

int Genetics::CPopulation::initialize(IChromosomeFactory const& chromosomeFactory) {
	for (int i = 0; i < m_size; ++i) m_chromosomes.push_back(chromosomeFactory.newChromosome());
	return 0;
}

int Genetics::CPopulation::evaluateFitness() {
	for (auto& chromosome : m_chromosomes) chromosome->evaluateFitness();
	return 0;
}