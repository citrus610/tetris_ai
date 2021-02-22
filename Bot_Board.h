#pragma once

#include <string>
#include <algorithm>
#include <math.h>
#include <array>
#include <vector>

#include "Bot_Piece.h"

namespace AI {
	class Bot_Board
	{
	public:
		static std::string encodeData(std::array<std::array<int, 10>, 40> board_data);
		static std::array<std::array <int, 10>, 40> decodeData(std::string code);

		static std::array<std::array <int, 10>, 40> placePiece(Bot_Piece _piece ,std::array<std::array <int, 10>, 40> _board_data);
		static std::vector<int> fullRowList(std::array<std::array <int, 10>, 40> _board_data);
		static std::array<std::array <int, 10>, 40> clearFullRow(std::vector<int> full_row_list, std::array<std::array <int, 10>, 40> _board_data);
		static std::array<int, 4> countGarbageSent(bool t_spin, bool _b2b, int _ren, std::vector<int> full_row_list, std::array<std::array <int, 10>, 40> _board_data); // 1st - garbage sent; 2nd - b2b; 3rd - ren; 4th - perfect clear
	private:
	};
};
