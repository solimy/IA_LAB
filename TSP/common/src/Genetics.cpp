#include "Genetics.h"

#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>

bool Genetics::FitnessComparator(Genetics::IChromosome* a, Genetics::IChromosome* b) { return a->getFitness() > b->getFitness(); }

Genetics::CPopulation::CPopulation(int size, double crossover_probability, double mutation_probability, int nb_parents, int nb_children) {
	m_size = size;
	m_pc = crossover_probability;
	m_pm = mutation_probability;
	m_nbParents = nb_parents;
	if (m_nbParents < 2) m_nbParents = 2;
	m_nbChildren = nb_children;
	if (m_nbChildren < 2) m_nbChildren = 2;
}

int Genetics::CPopulation::initialize(IChromosomeFactory const& chromosomeFactory) {
	std::srand(std::time(0));
	for (int i = 0; i < m_size; ++i) m_chromosomes.push_back(chromosomeFactory.newChromosome());
	evaluateFitness();
	return 0;
}

int Genetics::CPopulation::evaluateFitness() {
	for (auto& chromosome : m_chromosomes) chromosome->evaluateFitness();
	return 0;
}

Genetics::IChromosome* Genetics::CPopulation::findBest() {
	IChromosome* best = m_chromosomes.front();

	for (auto& chromosome : m_chromosomes) if (best->getFitness() < chromosome->getFitness()) best = chromosome;
	return best;
}

int Genetics::CPopulation::evolveOnce() {
	parentSelection();
	mate();
	evaluateFitness();
	survivorSelection();
	return 0;
}

int Genetics::CPopulation::parentSelection() {
/*	std::sort(m_chromosomes.begin(), m_chromosomes.end(), Genetics::FitnessComparator);
	for (int i = 0, j = m_chromosomes.size(); i < j && i < m_nbParents; ++i) m_parents.push_back(m_chromosomes[i]);
	return 0;*/
	double fitnessSum = 0;
	double choosen;
	double currentSum;

	for (auto& chromomosome : m_chromosomes) fitnessSum += chromomosome->getFitness();
	if (fitnessSum == 0) {
		for (int i = 0; i < m_nbParents; ++i) m_parents.push_back(m_chromosomes[i]);
		return 0;
	}
	for (int i = 0; i < m_nbParents; ++i) {
		choosen = (double)(std::rand() % (int)(fitnessSum * 1000)) / 1000;
		currentSum = 0;
		for (auto& chromosome : m_chromosomes) {
			currentSum += chromosome->getFitness();
			if (currentSum >= choosen) {
				m_parents.push_back(chromosome);
				break;
			}
		}
	}
	return 0;
}

int Genetics::CPopulation::mate() {
	int parent1, parent2;

	for (int i = 0; i < m_nbChildren; ++i) {
		parent1 = std::rand() % m_nbParents;
		parent2 = std::rand() % m_nbParents;
		if (parent1 == parent2 && parent1 == m_nbParents -1) {
			parent1 -= 1;
		} else if (parent1 == parent2 && parent1 < m_nbParents - 1) {
			parent2 += 1;
		}
		IChromosome* child = m_parents[parent1]->crossover(m_parents[parent2], m_pc);
		child->mutate(m_pm);
		m_chromosomes.push_back(child);
	}
	m_parents.clear();
	return 0;
}

int Genetics::CPopulation::survivorSelection() {
	std::sort(m_chromosomes.begin(), m_chromosomes.end(), Genetics::FitnessComparator);
	while (m_chromosomes.size() > m_size) {
		delete m_chromosomes.back();
		m_chromosomes.pop_back();
	}
	return 0;
}