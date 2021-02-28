#pragma once

#include <string>
#include <array>
#include <algorithm>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>

namespace AI {
	class Node
	{
	public:
		Node();
		~Node();

		std::array<std::array <int, 10>, 40> board;
		char hold = ' ';
		char current = ' ';
		std::vector<char> next;
		int ren = 0;
		bool b2b = false;

		float score = 0;
		float visit = 0;
		bool unexpandable = false;

		std::vector<std::shared_ptr<Node>> children;
		std::weak_ptr<Node> parent;

		std::string path;

		bool just_t_spin = false; // if just spin a t piece, then true, even if didn't clear any lines
		int just_cleared = 0;
		int just_sent = 0;
		std::string just_struct_tsd = ""; // number of current board TSD structure
		std::string just_struct_stsd = ""; // number of current board STSD structure
		std::string just_struct_tsttsd = ""; // number of current board TSTTSD structure
		bool just_perfect_clear = false;

		int total_sent = 0;
		int total_tspin_single = 0;
		int total_tspin_double = 0;
		int total_tspin_triple = 0;
		int total_burn_1 = 0;
		int total_burn_2 = 0;
		int total_burn_3 = 0;
		int total_tetris = 0;
		int total_perfect_clear = 0;
	};
};