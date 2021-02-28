#pragma once

#include "Node.h"
#include "Bot_Board.h"

namespace AI {
	struct Weight {
		float average_height = 0;
		float average_height_top_half = 0;
		float average_height_top_quarter = 0;
		float bumpiness = 0;
		float bumpiness_s = 0;
		float well = 0;
		float well_s = 0;
		float hole = 0;
		float overhang = 0;
		float block_above_hole = 0;
		float block_above_hole_s = 0;
		float column_height[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,0 };
		float column_well[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,0 };
		float structure[3] = { 0, 0, 0 };
		float waste_structure = 0;
		float b2b = 0;
		float ren = 0;
		float line_sent = 0;
		float perfect_clear = 0;
		float t_spin_1 = 0;
		float t_spin_2 = 0;
		float t_spin_3 = 0;
		float tetris = 0;
		float burn_1 = 0;
		float burn_2 = 0;
		float burn_3 = 0;
		float waste_time = 0;
	};

	class Evaluator
	{
	public:
		Evaluator();

		Weight weights;

		float evaluate(std::shared_ptr<Node> _node);

		// many more static functions to evaluate board
		static std::array<int, 10> column_height(std::array<std::array<int, 10>, 40> board_data);
		static std::array<int, 2> bumpiness(std::array<int, 10> _column_height);
		static std::array<int, 10> column_well(std::array<int, 10> _column_height);
		static std::array<int, 2> overhang_hole(std::array<std::array<int, 10>, 40> board_data, std::array<int, 10> _column_height);
		static std::array<int, 2> block_above_hole(std::array<std::array<int, 10>, 40> board_data, std::array<int, 10> _column_height);
		static std::array<std::string, 3> structure(std::array<std::array<int, 10>, 40> board_data, std::array<int, 10> _column_height);
	private:
	};
};
