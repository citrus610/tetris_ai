#pragma once

#include "Tree.h"
#include "Genetic_al_gen.h"

#include <fstream>
#include <random>

namespace AI {
	class Genetic_al
	{
	public:
		std::vector<Weight> population;

		void init(int size);

		void save();
		void set();
		std::string serialize(Weight _weight);

		Weight mutate(Weight w1, Weight w2);
		float v_mutate(float w1, float w2);

		float rand_1();
		float rand_0();

		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution_0;
		std::uniform_int_distribution<int> distribution_1;
	private:
	};
};

