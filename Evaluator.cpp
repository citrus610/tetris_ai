#include "Evaluator.h"

AI::Evaluator::Evaluator()
{
}

float AI::Evaluator::evaluate(Node* _node)
{
	float result = 0;

	std::array<std::array<int, 10>, 40> node_board_data = AI::Bot_Board::decodeData(_node->board);

	std::array<int, 10> node_column_height = AI::Evaluator::column_height(node_board_data);

	float total_height = 0;
	// count total height and each column height
	for (int i = 0; i < 10; i++) {
		total_height += node_column_height[i];
		result += node_column_height[i] * this->weights.column_height[i];
	}

	// average height
	result += total_height / 10 * this->weights.average_height;
	result += std::min(total_height / 10 - 10, 0.0f) * this->weights.average_height_top_half;
	result += std::min(total_height / 10 - 15, 0.0f) * this->weights.average_height_top_quarter;

	// bumpiness
	std::array<int, 2> node_bumpiness = AI::Evaluator::bumpiness(node_column_height);
	result += node_bumpiness[0] * this->weights.bumpiness;
	result += node_bumpiness[1] * this->weights.bumpiness_s;

	// well depth and column well depth
	std::array<int, 10> node_well = AI::Evaluator::column_well(node_column_height);
	float total_well = 0;
	float total_well_s = 0;
	for (int i = 0; i < 10; i++) {
		total_well += node_well[i];
		total_well_s += node_well[i] * node_well[i];
		result += node_well[i] * this->weights.column_well[i];
	}
	result += total_well * this->weights.well;
	result += total_well_s * this->weights.well_s;

	// hole and overhang
	std::array<int, 2> node_overhang_hole = AI::Evaluator::overhang_hole(node_board_data, node_column_height);
	result += node_overhang_hole[0] * this->weights.overhang;
	result += node_overhang_hole[1] * this->weights.hole;

	// number of block above hole
	std::array<int, 2> node_block_above_hole = AI::Evaluator::block_above_hole(node_board_data, node_column_height);
	result += node_block_above_hole[0] * this->weights.block_above_hole;
	result += node_block_above_hole[1] * this->weights.block_above_hole_s;

	// structure
	std::array<int, 3> node_structure = AI::Evaluator::structure(node_board_data, node_column_height);
	_node->just_struct_tsd = node_structure[0];
	_node->just_struct_stsd = node_structure[1];
	_node->just_struct_tsttsd = node_structure[2];
	result += _node->just_struct_tsd * this->weights.structure[0];
	result += _node->just_struct_stsd * this->weights.structure[1];
	result += _node->just_struct_tsttsd * this->weights.structure[2];

	// waste structure
	// DEFINE WASTE STRUCTURE: if the number of structures is smaller than the previous generation's, but there isn't any t spins, then structures are wasted
	if (!(_node->just_t_spin && _node->just_cleared > 0)) {
		if ((_node->just_struct_tsd < _node->parent->just_struct_tsd) || (_node->just_struct_stsd < _node->parent->just_struct_stsd) || (_node->just_struct_tsttsd < _node->parent->just_struct_tsttsd))
			result += this->weights.waste_structure;
	}

	// b2b and ren
	result += (int)_node->b2b * this->weights.b2b;
	result += _node->ren * this->weights.ren;

	// total line sent
	result += _node->total_sent * this->weights.line_sent;

	// perfect clear
	result += _node->total_perfect_clear * this->weights.perfect_clear;

	// t spin
	result += _node->total_tspin_single * this->weights.t_spin_1;
	result += _node->total_tspin_double * this->weights.t_spin_2;
	result += _node->total_tspin_triple * this->weights.t_spin_3;

	// tetris
	result += _node->total_tetris * this->weights.tetris;

	// burn lines
	result += _node->total_burn_1 * this->weights.burn_1;
	result += _node->total_burn_2 * this->weights.burn_2;
	result += _node->total_burn_3 * this->weights.burn_3;

	// waste time
	// DEFINITION: Time is wasted if softdrop a non-t piece, soft drop t piece without t spin, or clear lines
	int time_waste = 0;
	bool just_soft_drop = false;
	for (int i = 0; i < (int)_node->path.length(); i++) { // check if the path lead to current board state have "soft drop"
		if (_node->path[i] == 'S') {
			just_soft_drop = true;
			break;
		}
	}
	if (just_soft_drop) {
		// if just soft drop, but wasn't a t spin then wasted time
		if (!(_node->just_t_spin && _node->just_cleared > 0)) {
			time_waste++;
		}
	}
	if (_node->just_cleared < 4 && _node->just_cleared > 0 && !_node->just_t_spin && !_node->just_perfect_clear) {
		// if just cleared lines, but wasn't a t spin or tetris or perfect clear, then time was wasted
		time_waste++;
	}
	result += time_waste * this->weights.waste_time;
	
	return result;
}

std::array<int, 10> AI::Evaluator::column_height(std::array<std::array<int, 10>, 40> board_data)
{
	std::array<int, 10> result;

	for (int i = 0; i < 10; i++) {
		int height = 0;
		for (int k = 0; k < 40; k++) {
			if (board_data[k][i] > 0) {
				break;
			}
			else {
				height++;
			}
		}
		result[i] = 40 - height;
	}

	return result;
}

std::array<int, 2> AI::Evaluator::bumpiness(std::array<int, 10> _column_height)
{
	std::array<int, 2> result = { 0, 0};

	for (int i = 0; i < 9; i++) {
		result[0] += std::abs(_column_height[i] - _column_height[i + 1]);
		result[1] += (_column_height[i] - _column_height[i + 1]) * (_column_height[i] - _column_height[i + 1]);
	}

	return result;
}

std::array<int, 10> AI::Evaluator::column_well(std::array<int, 10> _column_height)
{
	std::array<int, 10> result = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	if (_column_height[1] - _column_height[0] > 0) {
		result[0] = _column_height[1] - _column_height[0];
	}
	if (_column_height[8] - _column_height[9] > 0) {
		result[9] = _column_height[8] - _column_height[9];
	}
	for (int i = 1; i < 9; i++) {
		if (_column_height[i - 1] > _column_height[i] && _column_height[i + 1] > _column_height[i]) {
			result[i] = (int)std::min(_column_height[i - 1] - _column_height[i], _column_height[i + 1] - _column_height[i]);
		}
	}

	return result;
}

std::array<int, 2> AI::Evaluator::overhang_hole(std::array<std::array<int, 10>, 40> board_data, std::array<int, 10> _column_height)
{
	std::array<int, 2> result = { 0, 0 };

	for (int i = 0; i < 10; i++) {
		for (int k = 40 - _column_height[i]; k < 40; k++) {
			// count overhang
			if (board_data[k][i] < 1) {
				result[0]++;
			}

			// count hole
			if (i == 0 && board_data[k][i] < 1 && board_data[k - 1][i] > 0 && board_data[k][i + 1] > 0) {
				result[1]++;
			}
			if (i == 9 && board_data[k][i] < 1 && board_data[k - 1][i] > 0 && board_data[k][i - 1] > 0) {
				result[1]++;
			}
			if (i != 0 && i != 9) {
				if (board_data[k][i] < 1 && board_data[k - 1][i] > 0 && board_data[k][i - 1] > 0 && board_data[k][i + 1] > 0) {
					result[1]++;
				}
			}
		}
	}

	return result;
}

std::array<int, 2> AI::Evaluator::block_above_hole(std::array<std::array<int, 10>, 40> board_data, std::array<int, 10> _column_height)
{
	std::array<int, 2> result = { 0, 0 };

	for (int i = 0; i < 10; i++) {
		int block_count = 0;
		int hole_count = 0;
		for (int k = 40 - _column_height[i]; k < 40; k++) {
			if (board_data[k][i] > 0) {
				block_count++;
			}
			else {
				hole_count++;
				break;
			}
		}
		if (hole_count > 0) {
			result[0] += block_count;
			result[1] += block_count * block_count;
		}
	}

	return result;
}

std::array<int, 3> AI::Evaluator::structure(std::array<std::array<int, 10>, 40> board_data, std::array<int, 10> _column_height)
{
	std::array<int, 3> result = { 0, 0, 0 };

	int max_height = 0;
	for (int i = 0; i < 10; i++) {
		if (_column_height[i] > max_height)
			max_height = _column_height[i];
	}

	// count t spin double structure
	// [ ].....          .....[ ]
	// ........    or    ........
	// [ ]..[ ]          [ ]..[ ]
	for (int i = 0; i < 8; i++) {
		for (int k = 40 - max_height; k < 38; k++) {
			if (board_data[k][i] > 0 && board_data[k][i + 1] == 0 && board_data[k][i + 2] == 0 &&
				board_data[k + 1][i] == 0 && board_data[k + 1][i + 1] == 0 && board_data[k + 1][i + 2] == 0 &&
				board_data[k + 2][i] > 0 && board_data[k + 2][i + 1] == 0 && board_data[k + 2][i + 2] > 0 &&
				_column_height[i + 1] < 40 - k && _column_height[i + 2] < 40 - k) {
				result[0]++;
			}
			if (board_data[k][i] == 0 && board_data[k][i + 1] == 0 && board_data[k][i + 2] > 0 &&
				board_data[k + 1][i] == 0 && board_data[k + 1][i + 1] == 0 && board_data[k + 1][i + 2] == 0 &&
				board_data[k + 2][i] > 0 && board_data[k + 2][i + 1] == 0 && board_data[k + 2][i + 2] > 0 &&
				_column_height[i] < 40 - k && _column_height[i + 1] < 40 - k) {
				result[0]++;
			}
		}
	}

	// count super t spin double structure
	// [ ]......          ......[ ]
	// .........          .........
	// ...[ ][ ]          [ ][ ]...
	// ......[ ]    or    [ ]......
	// ......[ ]          [ ]......
	// [ ][?][?]          [?][?][ ]
	for (int i = 0; i < 8; i++) {
		for (int k = 40 - max_height; k < 36; k++) {
			if (board_data[k][i] > 0 && board_data[k][i + 1] == 0 && board_data[k][i + 2] == 0 &&
				board_data[k + 1][i] == 0 && board_data[k + 1][i + 1] == 0 && board_data[k + 1][i + 2] == 0 &&
				board_data[k + 2][i] == 0 && board_data[k + 2][i + 1] > 0 && board_data[k + 2][i + 2] > 0 &&
				board_data[k + 3][i] == 0 && board_data[k + 3][i + 1] == 0 && board_data[k + 3][i + 2] > 0 &&
				board_data[k + 4][i] == 0 && board_data[k + 4][i + 1] == 0 && board_data[k + 4][i + 2] > 0 &&
				_column_height[i + 1] < 40 - k && _column_height[i + 2] < 40 - k) {
				if (k >= 35) {
					result[1]++;
				}
				else {
					if (board_data[k + 5][i] > 0)
						result[1]++;
				}
			}
			if (board_data[k][i] == 0 && board_data[k][i + 1] == 0 && board_data[k][i + 2] > 0 &&
				board_data[k + 1][i] == 0 && board_data[k + 1][i + 1] == 0 && board_data[k + 1][i + 2] == 0 &&
				board_data[k + 2][i] > 0 && board_data[k + 2][i + 1] > 0 && board_data[k + 2][i + 2] == 0 &&
				board_data[k + 3][i] > 0 && board_data[k + 3][i + 1] == 0 && board_data[k + 3][i + 2] == 0 &&
				board_data[k + 4][i] > 0 && board_data[k + 4][i + 1] == 0 && board_data[k + 4][i + 2] == 0 &&
				_column_height[i] < 40 - k && _column_height[i + 1] < 40 - k) {
				if (k >= 35) {
					result[1]++;
				}
				else {
					if (board_data[k + 5][i + 2] > 0)
						result[1]++;
				}
			}
		}
	}

	// count t spin triple -> t spin double structure
	// [ ]......          ......[ ]
	// .........          .........
	// ...[ ][ ]          [ ][ ]...
	// ......[ ]    or    [ ]......
	// ...[ ][ ]          [ ][ ]...
	// [ ]...[ ]          [ ]...[ ]
	for (int i = 0; i < 8; i++) {
		for (int k = 40 - max_height; k < 35; k++) {
			if (board_data[k][i] > 0 && board_data[k][i + 1] == 0 && board_data[k][i + 2] == 0 &&
				board_data[k + 1][i] == 0 && board_data[k + 1][i + 1] == 0 && board_data[k + 1][i + 2] == 0 &&
				board_data[k + 2][i] == 0 && board_data[k + 2][i + 1] > 0 && board_data[k + 2][i + 2] > 0 &&
				board_data[k + 3][i] == 0 && board_data[k + 3][i + 1] == 0 && board_data[k + 3][i + 2] > 0 &&
				board_data[k + 4][i] == 0 && board_data[k + 4][i + 1] > 0 && board_data[k + 4][i + 2] > 0 &&
				board_data[k + 5][i] > 0 && board_data[k + 5][i + 1] == 0 && board_data[k + 5][i + 2] > 0 &&
				_column_height[i + 1] < 40 - k && _column_height[i + 2] < 40 - k) {
				result[2]++;
			}
			if (board_data[k][i] == 0 && board_data[k][i + 1] == 0 && board_data[k][i + 2] > 0 &&
				board_data[k + 1][i] == 0 && board_data[k + 1][i + 1] == 0 && board_data[k + 1][i + 2] == 0 &&
				board_data[k + 2][i] > 0 && board_data[k + 2][i + 1] > 0 && board_data[k + 2][i + 2] == 0 &&
				board_data[k + 3][i] > 0 && board_data[k + 3][i + 1] == 0 && board_data[k + 3][i + 2] == 0 &&
				board_data[k + 4][i] > 0 && board_data[k + 4][i + 1] > 0 && board_data[k + 4][i + 2] == 0 &&
				board_data[k + 5][i] > 0 && board_data[k + 5][i + 1] == 0 && board_data[k + 5][i + 2] > 0 &&
				_column_height[i] < 40 - k && _column_height[i + 1] < 40 - k) {
				result[2]++;
			}
		}
	}

	return result;
}
