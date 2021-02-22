#pragma once

#include "Node.h"
#include "Bot_Board.h"
#include "Bot_Piece.h"

namespace AI {
	class Generator
	{
	public:
		Generator();

		std::unordered_map<char, std::vector<std::string>> path;

		void expand(Node* _node);
	private:
	};
};

