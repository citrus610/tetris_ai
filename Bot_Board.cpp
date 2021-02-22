#include "Bot_Board.h"

std::string AI::Bot_Board::encodeData(std::array<std::array<int, 10>, 40> board_data)
{
	std::string result;
	for (int i = 0; i < 40; i++) {
		int a_i = 0;
		int b_i = 0;
		for (int k = 0; k < 5; k++) {
			a_i += (int)std::min(1, board_data[i][k]) * std::pow(2, k);
			b_i += (int)std::min(1, board_data[i][k + 5]) * std::pow(2, k);
		}
		char a_c = a_i;
		char b_c = b_i;
		result.push_back(a_c);
		result.push_back(b_c);
	}
	return result;
}

std::array<std::array<int, 10>, 40> AI::Bot_Board::decodeData(std::string code)
{
	std::array<std::array<int, 10>, 40> result;
	for (int i = 0; i < 40; i++) {
		int a_i = code[i * 2];
		int b_i = code[i * 2 + 1];
		for (int k = 0; k < 5; k++) {
			result[i][k] = a_i % 2;
			result[i][k + 5] = b_i % 2;
			a_i = a_i / 2;
			b_i = b_i / 2;
		}
	}
	return result;
}

std::array<std::array<int, 10>, 40> AI::Bot_Board::placePiece(Bot_Piece _piece, std::array<std::array<int, 10>, 40> _board_data)
{
	std::array<std::array<int, 10>, 40> result = _board_data;
	for (int _y = 0; _y < (int)_piece.form[_piece.getType()][_piece.currentForm].size(); _y++) {
		for (int _x = 0; _x < (int)_piece.form[_piece.getType()][_piece.currentForm][_y].size(); _x++) {
			if (_piece.form[_piece.getType()][_piece.currentForm][_y][_x] > 0) {
				result[_y + _piece.y][_x + _piece.x] = _piece.form[_piece.getType()][_piece.currentForm][_y][_x];
			}
		}
	}
	return result;
}

std::vector<int> AI::Bot_Board::fullRowList(std::array<std::array<int, 10>, 40> _board_data)
{
	std::vector<int> result;
	for (int i = 20; i < 40; i++) {
		int row_product = 1;
		for (int k = 0; k < 10; k++) {
			row_product = row_product * _board_data[i][k];
		}
		if (row_product > 0) {
			result.push_back(i);
		}
	}
	return result;
}

std::array<std::array <int, 10>, 40> AI::Bot_Board::clearFullRow(std::vector<int> full_row_list, std::array<std::array<int, 10>, 40> _board_data)
{
	std::array<std::array<int, 10>, 40> result = _board_data;
	for (int i = 0; i < (int)full_row_list.size(); i++) {
		for (int k = full_row_list[i]; k > 0; k--) {
			result[k] = result[k - 1];
		}
		result[0] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	}
	return result;
}

std::array<int, 4> AI::Bot_Board::countGarbageSent(bool t_spin, bool _b2b, int _ren, std::vector<int> full_row_list, std::array<std::array<int, 10>, 40> _board_data)
{
	std::array<int, 4> result;

	// 1st - garbage sent; 2nd - b2b; 3rd - ren
	int garbage = 0;
	bool b2b = _b2b;
	int ren = _ren;

	if (t_spin) {
		garbage = full_row_list.size() * 2;
		if (_b2b)
			garbage++;
		b2b = true;
	}
	else {
		switch (full_row_list.size())
		{
		case 0:
			break;
		case 4:
			garbage = 4;
			if (_b2b)
				garbage++;
			b2b = true;
			break;
		default:
			b2b = false;
			garbage = full_row_list.size() - 1;
			break;
		}
	}

	// find if perfect clear
	int not_full_or_full_row_count = 0;
	for (int i = 20; i < 40; i++) {
		int row_sum = 0;
		int row_product = 1;
		for (int k = 0; k < 10; k++) {
			row_sum += _board_data[i][k];
			row_product *= _board_data[i][k];
		}
		if ((row_sum == 0) || (row_product > 0)) {
			not_full_or_full_row_count++;
		}
	}
	if (not_full_or_full_row_count == 20) {
		garbage = 10;
		result[3] = 1;
	}
	else {
		result[3] = 0;
	}

	// ren
	if (full_row_list.size() > 0) {
		ren++;
	}
	else {
		ren = 0;
	}
	if (ren < 10) {
		garbage += (ren - (ren % 2)) / 2;
	}
	else if (ren == 10) {
		garbage += 4;
	}
	else {
		garbage += 5;
	}

	result[0] = garbage;
	result[1] = (int)b2b;
	result[2] = ren;

	return result;
}
