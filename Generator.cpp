#include "Generator.h"

AI::Generator::Generator()
{
	this->path['O'] = {
		"LLLLH",
		"LLLH",
		"LLH",
		"LH",
		"H",
		"RH",
		"RRH",
		"RRRH",
		"RRRRH",

		"LLLLSRH",
		"LLLSRH",
		"LLSRH",
		"LSRH",
		"SRH",
		"RSRH",
		"RRSRH",
		"RRRSRH",

		"LLLSLH",
		"LLSLH",
		"LSLH",
		"SLH",
		"RSLH",
		"RRSLH",
		"RRRSLH",
		"RRRRSLH"
	};
	this->path['I'] = {
		"LLLH",
		"LLH",
		"LH",
		"H",
		"RH",
		"RRH",
		"RRRH",

		"XLLLLLH",
		"XLLLLH",
		"XLLLH",
		"XLLH",
		"XLH",
		"XH",
		"XRH",
		"XRRH",
		"XRRRH",
		"XRRRRH",

		"LLLSRH",
		"LLSRH",
		"LSRH",
		"SRH",
		"RSRH",
		"RRSRH",

		"LLSLH",
		"LSLH",
		"SLH",
		"RSLH",
		"RRSLH",
		"RRRSLH",

		"XLLLLLSRH",
		"XLLLLSRH",
		"XLLLSRH",
		"XLLSRH",
		"XLSRH",
		"XSRH",
		"XRSRH",
		"XRRSRH",
		"XRRRSRH",

		"XLLLLSLH",
		"XLLLSLH",
		"XLLSLH",
		"XLSLH",
		"XSLH",
		"XRSLH",
		"XRRSLH",
		"XRRRSLH",
		"XRRRRSLH",
	};
	this->path['T'] = {
		// hard drop only
		"LLLH",
		"LLH",
		"LH",
		"H",
		"RH",
		"RRH",
		"RRRH",
		"RRRRH",

		"XLLLLH",
		"XLLLH",
		"XLLH",
		"XLH",
		"XH",
		"XRH",
		"XRRH",
		"XRRRH",
		"XRRRRH",

		"XXLLLH",
		"XXLLH",
		"XXLH",
		"XXH",
		"XXRH",
		"XXRRH",
		"XXRRRH",
		"XXRRRRH",

		"ZLLLH",
		"ZLLH",
		"ZLH",
		"ZH",
		"ZRH",
		"ZRRH",
		"ZRRRH",
		"ZRRRRH",
		"ZRRRRRH",

		// soft drop and tuck right and left

		"LLLSRH",
		"LLSRH",
		"LSRH",
		"SRH",
		"RSRH",
		"RRSRH",
		"RRRSRH",

		"LLSLH",
		"LSLH",
		"SLH",
		"RSLH",
		"RRSLH",
		"RRRSLH",
		"RRRRSLH",

		"XLLLLSRH",
		"XLLLSRH",
		"XLLSRH",
		"XLSRH",
		"XSRH",
		"XRSRH",
		"XRRSRH",
		"XRRRSRH",

		"XLLLSLH",
		"XLLSLH",
		"XLSLH",
		"XSLH",
		"XRSLH",
		"XRRSLH",
		"XRRRSLH",
		"XRRRRSLH",

		"XXLLLSRH",
		"XXLLSRH",
		"XXLSRH",
		"XXSRH",
		"XXRSRH",
		"XXRRSRH",
		"XXRRRSRH",

		"XXLLSLH",
		"XXLSLH",
		"XXSLH",
		"XXRSLH",
		"XXRRSLH",
		"XXRRRSLH",
		"XXRRRRSLH",

		"ZLLLSRH",
		"ZLLSRH",
		"ZLSRH",
		"ZSRH",
		"ZRSRH",
		"ZRRSRH",
		"ZRRRSRH",
		"ZRRRRSRH",

		"ZLLSLH",
		"ZLSLH",
		"ZSLH",
		"ZRSLH",
		"ZRRSLH",
		"ZRRRSLH",
		"ZRRRRSLH",
		"ZRRRRRSLH",

		// soft drop then rotate

		"LLLSXH",
		"LLSXH",
		"LSXH",
		"SXH",
		"RSXH",
		"RRSXH",
		"RRRSXH",
		"RRRRSXH",
		
		"LLLSZH",
		"LLSZH",
		"LSZH",
		"SZH",
		"RSZH",
		"RRSZH",
		"RRRSZH",
		"RRRRSZH",
		
		"XLLLLSXH",
		"XLLLSXH",
		"XLLSXH",
		"XLSXH",
		"XSXH",
		"XRSXH",
		"XRRSXH",
		"XRRRSXH",
		"XRRRRSXH",

		"XLLLLSZH",
		"XLLLSZH",
		"XLLSZH",
		"XLSZH",
		"XSZH",
		"XRSZH",
		"XRRSZH",
		"XRRRSZH",
		"XRRRRSZH",

		"XXLLLSXH",
		"XXLLSXH",
		"XXLSXH",
		"XXSXH",
		"XXRSXH",
		"XXRRSXH",
		"XXRRRSXH",
		"XXRRRRSXH",

		"XXLLLSZH",
		"XXLLSZH",
		"XXLSZH",
		"XXSZH",
		"XXRSZH",
		"XXRRSZH",
		"XXRRRSZH",
		"XXRRRRSZH",

		"ZLLLSXH",
		"ZLLSXH",
		"ZLSXH",
		"ZSXH",
		"ZRSXH",
		"ZRRSXH",
		"ZRRRSXH",
		"ZRRRRSXH",
		"ZRRRRRSXH",

		"ZLLLSZH",
		"ZLLSZH",
		"ZLSZH",
		"ZSZH",
		"ZRSZH",
		"ZRRSZH",
		"ZRRRSZH",
		"ZRRRRSZH",
		"ZRRRRRSZH",

		// t spin triple move
			// tuck and rotate

		"LLLSRZH",
		"LLSRZH",
		"LSRZH",
		"SRZH",
		"RSRZH",
		"RRSRZH",
		"RRRSRZH",

		"LLSLXH",
		"LSLXH",
		"SLXH",
		"RSLXH",
		"RRSLXH",
		"RRRSLXH",
		"RRRRSLXH",

			// rotate and rotate
		"XLLLLSZZH",
		"XLLLSZZH",
		"XLLSZZH",
		"XLSZZH",
		"XSZZH",
		"XRSZZH",
		"XRRSZZH",
		"XRRRSZZH",

		"ZLLSXXH",
		"ZLSXXH",
		"ZSXXH",
		"ZRSXXH",
		"ZRRSXXH",
		"ZRRRSXXH",
		"ZRRRRSXXH",
		"ZRRRRRSXXH",
	};
	this->path['J'] = this->path['T'];
	this->path['L'] = this->path['T'];
	this->path['S'] = this->path['T'];
	this->path['Z'] = this->path['T'];

}

/*
	L - move left
	R - move right
	H - hard drop
	S - soft drop
	C - hold
	X - rotate right
	Z - rotate left
*/

/*
The expand function: create children from the current node state
Maybe this is the most expensive and unsafe function

NOTE TO SELF: TO DETERMINE A MOVE THAT RESULT IN AN ALREADY EXIST BOARD STATE, COMPARE PIECE X, Y, AND ROTATION
*/

void AI::Generator::expand(Node* _node)
{
	if (_node->current == ' ')
		return;

	std::vector<std::string> possible_paths; // store all possible paths
	std::vector<std::string> piece_data_storage; // store all unique x, y, rotation state; if a path lead to the same piece state then don't add it
	std::vector<std::string> uncertain_paths; // paths that need to be checked
	Bot_Piece bot_piece; // a piece to attempt paths
	std::array<std::array<int, 10>, 40> board_data = Bot_Board::decodeData(_node->board);

	// find all possible paths (paths that don't result in game over or same board state)
		// check with current piece
	uncertain_paths = this->path[_node->current];
	for (int i = 0; i < (int)uncertain_paths.size(); i++) {
		bot_piece.setType(_node->current);
		bot_piece.init();
		bot_piece.attempt(uncertain_paths[i], board_data);

		// if dead then ignore
		if (bot_piece.y <= 18) {
			// dumb space
		}
		else {
			std::string piece_data;
			piece_data.push_back((char)bot_piece.x);
			piece_data.push_back((char)bot_piece.y);
			piece_data.push_back((char)bot_piece.currentForm);

			bool is_exist = false;

			// check if game over or same board state as before
			if (i == 0) { // if this is the first time then ignore
				// dumb space
			}
			else {
				for (int k = 0; k < (int)piece_data_storage.size(); k++) {
					if (piece_data == piece_data_storage[k]) {
						is_exist = true;
						break;
					}
				}
			}

			if (is_exist) { // if board state had already exist then ignore
				// dumb space
			}
			else {
				piece_data_storage.push_back(piece_data);
				possible_paths.push_back(uncertain_paths[i]);
			}
		}
	}

		// check with hold piece
	uncertain_paths.clear();
	piece_data_storage.clear();
	if (_node->hold == ' ') {
		// if there is no hold piece and next piece, then ignore
		if (_node->next.length() < 1) { }
		else {
			// if there is no hold piece, then the bot_piece will be the next piece
			uncertain_paths = this->path[_node->next[0]];
			for (int i = 0; i < (int)uncertain_paths.size(); i++) {
				bot_piece.setType(_node->next[0]);
				bot_piece.init();
				bot_piece.attempt(uncertain_paths[i], board_data);

				if (bot_piece.y <= 18) {
				}
				else {
					std::string piece_data;
					piece_data.push_back((char)bot_piece.x);
					piece_data.push_back((char)bot_piece.y);
					piece_data.push_back((char)bot_piece.currentForm);

					bool is_exist = false;

					if (i == 0) {
					}
					else {
						for (int k = 0; k < (int)piece_data_storage.size(); k++) {
							if (piece_data == piece_data_storage[k]) {
								is_exist = true;
								break;
							}
						}
					}

					if (is_exist) {
					}
					else {
						piece_data_storage.push_back(piece_data);
						std::string to_add = uncertain_paths[i];
						to_add.insert(to_add.begin(), 'C');
						possible_paths.push_back(to_add);
					}
				}
			}
		}
	}
	else {
		// if there is hold piece, then the bot_piece will be hold piece
		uncertain_paths = this->path[_node->hold];
		for (int i = 0; i < (int)uncertain_paths.size(); i++) {
			bot_piece.setType(_node->hold);
			bot_piece.init();
			bot_piece.attempt(uncertain_paths[i], board_data);

			if (bot_piece.y <= 18) {
			}
			else {
				std::string piece_data;
				piece_data.push_back((char)bot_piece.x);
				piece_data.push_back((char)bot_piece.y);
				piece_data.push_back((char)bot_piece.currentForm);

				bool is_exist = false;

				if (i == 0) {
				}
				else {
					for (int k = 0; k < (int)piece_data_storage.size(); k++) {
						if (piece_data == piece_data_storage[k]) {
							is_exist = true;
							break;
						}
					}
				}

				if (is_exist) {
				}
				else {
					piece_data_storage.push_back(piece_data);
					std::string to_add = uncertain_paths[i];
					to_add.insert(to_add.begin(), 'C');
					possible_paths.push_back(to_add);
				}
			}
		}
	}

	// after having all possible paths, we then create node's children
	// WARNING: creating children can cause memory leak without caution
	for (int i = 0; i < (int)possible_paths.size(); i++) {
		Node* child = new Node;
		child->path = possible_paths[i];
		child->parent = _node;
		_node->children.push_back(child);
		if (possible_paths[i][0] == 'C') {
			if (_node->hold == ' ') { // if there is no hold piece
				bot_piece.setType(_node->next[0]);
				child->hold = _node->current;
				if (_node->next.length() < 2) { // if there is only 1 next piece then the child is unexpandable
					child->unexpandable = true;
					child->current = ' ';
				}
				else {
					child->current = _node->next[1];
					child->next = _node->next;
					child->next.erase(child->next.begin(), child->next.begin() + 1);
				}
			}
			else { // if there is hold piece
				bot_piece.setType(_node->hold);
				child->hold = _node->current;
				if (_node->next.length() < 1) { // if there is no next piece then the child is unexpandable
					child->unexpandable = true;
					child->current = ' ';
				}
				else { // if there is next piece then the child's current piece will be its parent's next piece
					child->current = _node->next[0];
					child->next = _node->next;
					child->next.erase(child->next.begin());
				}
			}
		}
		else {
			bot_piece.setType(_node->current);
			child->hold = _node->hold;
			if (_node->next.length() < 1) { // if there is no next piece then the child is unexpandable
				child->unexpandable = true;
				child->current = ' ';
			}
			else { // if there is next piece then the child's current piece will be its parent's next piece
				child->current = _node->next[0];
				child->next = _node->next;
				child->next.erase(child->next.begin());
			}
		}

		// simulate move to get board data, ren, b2b, lines sent, lines cleared, etc...
		std::string the_path = possible_paths[i];
		if (the_path[0] == 'C')
			the_path.erase(the_path.begin());
		bot_piece.init();
		bot_piece.attempt(the_path, board_data);
		bool just_t_spin = bot_piece.justTSpin(board_data); // check if just t spin
		std::array<std::array<int, 10>, 40> board_data_after_place_piece = AI::Bot_Board::placePiece(bot_piece, board_data); // get the new board state after place piece (hadn't cleared any lines)
		std::vector<int> full_row_list = AI::Bot_Board::fullRowList(board_data_after_place_piece); // get the list of full rows
		std::array<int, 4> garbage_b2b_ren_pc = AI::Bot_Board::countGarbageSent(just_t_spin, _node->b2b, _node->ren, full_row_list, board_data_after_place_piece);
		int _line_sent = garbage_b2b_ren_pc[0]; // get total line sent
		bool _b2b = (bool)garbage_b2b_ren_pc[1]; // get b2b state
		int _ren = garbage_b2b_ren_pc[2]; // get ren counter
		int _pc = garbage_b2b_ren_pc[3]; // get perfect clear
		std::array<std::array<int, 10>, 40> board_data_after_clear_lines = AI::Bot_Board::clearFullRow(full_row_list, board_data_after_place_piece); // get the final board state

		// set data to child
		child->board = AI::Bot_Board::encodeData(board_data_after_clear_lines);
		child->b2b = _b2b;
		child->ren = _ren;

		child->just_t_spin = just_t_spin;
		child->just_cleared = (int)full_row_list.size();
		child->just_sent = _line_sent;
		child->just_perfect_clear = (bool)_pc;

		child->total_sent = _node->total_sent + child->just_sent;
		child->total_perfect_clear = _node->total_perfect_clear + child->just_perfect_clear;
		if (child->just_cleared > 0) {
			if (just_t_spin) {
				if (child->just_cleared == 1) {
					child->total_tspin_single = _node->total_tspin_single + 1;
				}
				else if (child->just_cleared == 2) {
					child->total_tspin_double = _node->total_tspin_double + 1;
				}
				else if (child->just_cleared == 3) {
					child->total_tspin_triple = _node->total_tspin_triple + 1;
				}
			}
			else {
				if (child->just_cleared == 1) {
					child->total_burn_1 = _node->total_burn_1 + 1;
				}
				else if (child->just_cleared == 2) {
					child->total_burn_2 = _node->total_burn_2 + 1;
				}
				else if (child->just_cleared == 3) {
					child->total_burn_3 = _node->total_burn_3 + 1;
				}
				else {
					child->total_tetris = _node->total_tetris + 1;
				}
			}
		}
	}
}
