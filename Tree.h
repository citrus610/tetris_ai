#pragma once

#include "Evaluator.h"
#include "Generator.h"

namespace AI {
	class Tree
	{
	public:
		Tree();
		~Tree();
		Generator generator;
		Evaluator evaluator;

		Node* root;

		float getUBC(Node* _node);
		Node* getBestChild(Node* _node);
		void backpropagate(Node* _node);
		bool isUnexpandable(Node* _node);

		void setRootState(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::vector<char> next, bool b2b, int ren);
		void setRootState(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::string next, bool b2b, int ren);
		void addPiece(Node* _node, char _piece); // add a piece to the next piece queue
		void shiftNext(int index);
		void reset(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::vector<char> next, bool b2b, int ren); // reset tree because in case of receving garbage, etc... where the board state is different from what the bot predicted
		void reset(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::string next, bool b2b, int ren); // reset tree because in case of receving garbage, etc... where the board state is different from what the bot predicted
		void deleteNode(Node* _node);

		// temporary for testing, will remove later
		std::string findMove(std::array<std::array<int, 10>, 40> _board_data);
	private:
	};
};

