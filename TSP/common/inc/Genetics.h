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

namespace Genetics_v2 {

	class IChromosome {};

	namespace EngineOptions {
		
		enum class EParentsSelection : int {
			FITNESS_PROPORTIONATE,
			ROULETTE_WHEEL,
			TOURNAMENT,
			RANK,
			RANDOM,
			CUSTOM,
			LAST
		};

		enum class ECrossover {
			ONE_POINT,
			MULTI_POINT,
			UNIFORM,
			OX1,
			CUSTOM,
			LAST
		};

		enum class EMutation {
			RANDOM_RESETTING,
			SWAP,
			SCRAMBLE,
			INVERSION,
			CUSTOM,
			LAST
		};

		enum class ESruvivorSelection {
			AGE_BASED,
			FITNESS_BASED,
			CUSTOM,
			LAST
		};
	}

	class CGeneticEngine {
	private:
		void (*m_parentSelection)(std::vector<IChromosome*>& population, std::vector<IChromosome*>& parents);
		void (*m_crossover)(std::vector<IChromosome*>& population, std::vector<IChromosome*>& parents);
		void (*m_mutation)(std::vector<IChromosome*>& children);
		void (*m_survivorSelection)(std::vector<IChromosome*>& population);

	public:
		CGeneticEngine();
		void run();

		void setOption(EngineOptions::EParentsSelection);
		void setOption(EngineOptions::ECrossover);
		void setOption(EngineOptions::EMutation);
		void setOption(EngineOptions::ESruvivorSelection);
	};

}

#endif // !GENETICS_H_
