#pragma once

#include <string>
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

		std::string board;
		char hold;
		char current;
		std::string next;
		int ren;
		bool b2b;

		float score = 0;
		int visit = 0;
		bool unexpandable = false;

		std::vector<Node*> children;
		Node* parent;

		std::string path;

		bool just_t_spin = false; // if just spin a t piece, then true, even if didn't clear any lines
		int just_cleared = 0;
		int just_sent = 0;
		int just_struct_tsd = 0; // number of current board TSD structure
		int just_struct_stsd = 0; // number of current board STSD structure
		int just_struct_tsttsd = 0; // number of current board TSTTSD structure
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