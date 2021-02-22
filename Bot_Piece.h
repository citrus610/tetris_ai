#pragma once

#include <unordered_map>
#include <array>
#include <vector>

namespace AI {
	class Bot_Piece
	{
	public:
		Bot_Piece();

		int x = 0;
		int y = 0;
		int currentForm = 0;

		void init();

		void setType(char type);
		char getType();

		bool isColliding(int _x, int _y, std::array<std::array<int, 10>, 40> board_data);
		bool isImmobile(std::array<std::array<int, 10>, 40> board_data);
		bool justTSpin(std::array<std::array<int, 10>, 40> board_data);

		void tryLeft(std::array<std::array<int, 10>, 40> board_data);
		void tryRight(std::array<std::array<int, 10>, 40> board_data);
		void tryDown(std::array<std::array<int, 10>, 40> board_data);
		void tryHardDrop(std::array<std::array<int, 10>, 40> board_data);
		void tryRotate(int direction, std::array<std::array<int, 10>, 40> board_data);

		void attempt(std::string _path, std::array<std::array<int, 10>, 40> board_data);

		std::unordered_map<char, std::vector<std::vector<std::vector<int>>>> form;
	private:
		char type = ' ';

		std::unordered_map<char, int> initPos;
		std::unordered_map<char, std::vector<std::vector<std::vector<int>>>> srsData;
	};
};
