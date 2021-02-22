#pragma once

#include "Node.h"
#include "Bot_Board.h"

namespace AI {
	struct Weight {
		float average_height = -0.039f;
		float average_height_top_half = -0.115f;
		float average_height_top_quarter = -0.150f;
		float bumpiness = -0.017f;
		float bumpiness_s = -0.001f;
		float well = 0.017f;
		float well_s = 0.001f;
		float hole = -0.173f;
		float overhang = -0.088f;
		float block_above_hole = -0.017f;
		float block_above_hole_s = -0.001f;
		float column_height[10] = { -0.01f, -0.01f, -0.01f, -0.01f, -0.01f, -0.01f, -0.01f, -0.01f, -0.01f, -0.01f };
		float column_well[10] = { 0.020f, 0.023f, 0.020f, 0.050f, 0.059f, 0.021f, 0.059f, 0.010f, -0.010f, 0.024f };
		float structure[3] = { 0.148f, 0.192f, 0.407f };
		float waste_structure = -0.152f;
		float b2b = 0.052f;
		float ren = 0.006f;
		float line_sent = 0.001f;
		float perfect_clear = 1.0f;
		float t_spin_1 = 0.121f;
		float t_spin_2 = 0.410f;
		float t_spin_3 = 0.602f;
		float tetris = 0.390f;
		float burn_1 = -0.143f;
		float burn_2 = -0.100f;
		float burn_3 = -0.058f;
		float waste_time = -0.003f;
	};

	class Evaluator
	{
	public:
		Evaluator();

		Weight weights;

		float evaluate(Node* _node);

		// many more static functions to evaluate board
		static std::array<int, 10> column_height(std::array<std::array<int, 10>, 40> board_data);
		static std::array<int, 2> bumpiness(std::array<int, 10> _column_height);
		static std::array<int, 10> column_well(std::array<int, 10> _column_height);
		static std::array<int, 2> overhang_hole(std::array<std::array<int, 10>, 40> board_data, std::array<int, 10> _column_height);
		static std::array<int, 2> block_above_hole(std::array<std::array<int, 10>, 40> board_data, std::array<int, 10> _column_height);
		static std::array<int, 3> structure(std::array<std::array<int, 10>, 40> board_data, std::array<int, 10> _column_height);
	private:
	};
};
