#ifndef GENETICS_H_
#define GENETICS_H_

#include <vector>

namespace Genetics {

	/*GA()
   __initialize population
   __find fitness of population
   
   while (termination criteria is reached) do
      parent selection
      crossover with probability pc
      mutation with probability pm
      __decode and fitness calculation
      survivor selection
      __find best
   return best*/

	/*
	*/
	class IChromosome {
	public:
		virtual IChromosome* crossover(IChromosome* chromosome, double rate) = 0;
		virtual int mutate(double rate) = 0;
		virtual int evaluateFitness() = 0;
		virtual double getFitness() = 0;
	};

	bool FitnessComparator(IChromosome* a, IChromosome* b);

	class IChromosomeFactory {
	public:
		virtual IChromosome* newChromosome() const = 0;
	};

	class CPopulation {
	public:
		int m_size;
		double m_pc;
		double m_pm;
		int m_nbParents;
		int m_nbChildren;
		std::vector<IChromosome*> m_parents;
		std::vector<IChromosome*> m_chromosomes;

	public:
		CPopulation(int size, double crossover_probability, double mutation_probability, int nb_parents, int nb_children);
		int initialize(IChromosomeFactory const& chromosomeFactory);
		int evaluateFitness();
		int parentSelection();
		int mate();
		int survivorSelection();
		IChromosome* findBest();
		int evolveOnce();
	};
}

#endif // !GENETICS_H_
