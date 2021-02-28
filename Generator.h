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

		void expand(std::shared_ptr<Node> _node);
	private:
	};
};

