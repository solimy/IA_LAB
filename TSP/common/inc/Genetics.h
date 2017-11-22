#ifndef GENETICS_H_
#define GENETICS_H_

#include <vector>

namespace Genetics {

	/*GA()
   initialize population
   find fitness of population
   
   while (termination criteria is reached) do
      parent selection
      crossover with probability pc
      mutation with probability pm
      decode and fitness calculation
      survivor selection
      find best
   return best*/

	/*
	*/
	class ICromosome {
	public:
		virtual int crossover(ICromosome& chromosome) = 0;
		virtual int mutate() = 0;
		virtual int evaluateFitness() = 0;
		virtual double getFitness() = 0;
	};

	class IChromosomeFactory {
	public:
		virtual ICromosome* newChromosome() const = 0;
	};

	class CPopulation {
		int m_size;
		double m_pc;
		double m_pm;
		std::vector<ICromosome*> m_chromosomes;

	public:
		CPopulation(int size, double crossover_probability, double mutation_probability);
		int initialize(IChromosomeFactory const& chromosomeFactory);
		int evaluateFitness();
	};

	namespace Default {

		template<typename GENE>
		class Chromosome : public ICromosome {
			double m_fitness;
		public:
			int crossover(ICromosome& chromosome) { return 0; }
			int mutate() { return 0; }
			int evaluateFitness() { return 0; }
			double getFitness() { return m_fitness; }
		};

		template<typename CHROMOSOME>
		class ChromosomeFactory : public IChromosomeFactory {
		public:
			ICromosome* newChromosome() const { return new CHROMOSOME(); }
		};
	}
}

#endif // !GENETICS_H_
