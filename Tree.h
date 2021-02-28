#pragma once

#include "Evaluator.h"
#include "Generator.h"
#include "Bot_Board.h"
#include "Bot_Piece.h"

namespace AI {
	class Tree
	{
	public:
		Tree();
		~Tree();
		Generator generator;
		Evaluator evaluator;
		Bot_Board s_board;

		std::shared_ptr<Node> root;

		float getUBC(std::shared_ptr<Node> _node);
		std::shared_ptr<Node> getBestChild(std::shared_ptr<Node> _node);
		void backpropagate(std::shared_ptr<Node> _node);
		bool isUnexpandable(std::shared_ptr<Node> _node);
		void reviveDead(std::shared_ptr<Node> _node);

		void setRootState(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::vector<char> next, bool b2b, int ren);
		void setRootState(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::string next, bool b2b, int ren);
		void addPiece(std::shared_ptr<Node> _node, char _piece); // add a piece to the next piece queue
		void shiftNext(int index);
		void reset(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::vector<char> next, bool b2b, int ren); // reset tree because in case of receving garbage, etc... where the board state is different from what the bot predicted
		void reset(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::string next, bool b2b, int ren); // reset tree because in case of receving garbage, etc... where the board state is different from what the bot predicted
		//void deleteNode(Node* _node);

		// temporary for testing, will remove later
		std::string findMove(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::vector<char> next, bool b2b, int ren);
	private:
	};
};

