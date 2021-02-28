#include "Bot_Board.h"

void AI::Bot_Board::attempt(std::string _path, std::shared_ptr<Node> _node)
{
	this->piece.setType(this->current);
	this->piece.init();
	for (int i = 0; i < (int)_path.length(); i++) {
		switch (_path[i])
		{
		case 'L':
			this->piece.tryLeft(this->data);
			break;
		case 'R':
			this->piece.tryRight(this->data);
			break;
		case 'C':
			if (this->hold == ' ') {
				this->hold = this->current;
				this->current = this->next[0];
				this->next.erase(this->next.begin());
			}
			else {
				char value = this->hold;
				this->hold = this->current;
				this->current = value;
			}
			this->piece.setType(this->current);
			this->piece.init();
			break;
		case 'X':
			this->piece.tryRotate(1, this->data);
			break;
		case 'Z':
			this->piece.tryRotate(3, this->data);
			break;
		case 'H':
			this->piece.tryHardDrop(this->data);
			break;
		case 'S':
			this->piece.tryHardDrop(this->data);
			break;
		default:
			break;
		}
	}

	bool _t_spin = this->piece.justTSpin(this->data);
	this->data = AI::Bot_Board::placePiece(this->piece, this->data);
	std::vector<int> _full_row_list = AI::Bot_Board::fullRowList(this->data);
	std::array<int, 4> _g_b_r_pc = AI::Bot_Board::countGarbageSent(_t_spin, this->b2b, this->ren, _full_row_list, this->data);
	this->data = AI::Bot_Board::clearFullRow(_full_row_list, this->data);
	this->b2b = _g_b_r_pc[1];
	this->ren = _g_b_r_pc[2];

	if (this->next.size() > 0) {
		this->current = this->next[0];
		this->next.erase(this->next.begin());
	}
	else {
		this->current = ' ';
	}

	// set node data
	_node->board = AI::Bot_Board::normalize(this->data);
	_node->current = this->current;
	_node->hold = this->hold;
	_node->next = this->next;

	_node->just_t_spin = _t_spin;
	_node->just_cleared = _full_row_list.size();
	_node->just_sent = _g_b_r_pc[0];
	_node->just_perfect_clear = _g_b_r_pc[3];

	if (_t_spin) {
		if (_node->just_cleared == 1) {
			_node->total_tspin_single = _node->parent.lock()->total_tspin_single + 1;
		}else if (_node->just_cleared == 2) {
			_node->total_tspin_double = _node->parent.lock()->total_tspin_double + 1;
		}else if (_node->just_cleared == 3) {
			_node->total_tspin_triple = _node->parent.lock()->total_tspin_triple + 1;
		}
	}
	else {
		if (_node->just_cleared == 1) {
			_node->total_burn_1 = _node->parent.lock()->total_burn_1 + 1;
		}
		else if (_node->just_cleared == 2) {
			_node->total_burn_2 = _node->parent.lock()->total_burn_2 + 1;
		}
		else if (_node->just_cleared == 3) {
			_node->total_burn_3 = _node->parent.lock()->total_burn_3 + 1;
		}
		else {
			_node->total_tetris = _node->parent.lock()->total_tetris + 1;
		}
	}

	_node->total_sent = _node->just_sent + _node->parent.lock()->total_sent;
	_node->total_perfect_clear = _node->just_perfect_clear + _node->parent.lock()->total_perfect_clear;
}

void AI::Bot_Board::setState(std::array<std::array<int, 10>, 40> _board_data, char _current, char _hold, std::vector<char> _next, bool _b2b, int _ren)
{
	this->data = _board_data;
	this->current = _current;
	this->hold = _hold;
	this->next = _next;
	this->b2b = _b2b;
	this->ren = _ren;

	this->piece.setType(this->current);
	this->piece.init();
}

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

std::array<std::array<int, 10>, 40> AI::Bot_Board::normalize(std::array<std::array<int, 10>, 40> board_data)
{
	std::array<std::array<int, 10>, 40> result;

	for (int i = 0; i < 40; i++) {
		for (int k = 0; k < 10; k++) {
			result[i][k] = std::min(board_data[i][k], 1);
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
