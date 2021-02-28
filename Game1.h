#pragma once

#include "Game.h"
#include "Tree.h"
#include "Genetic_al.h"

class Game1 :
	public Game
{
public:
	void load() override;
	void update(float dt) override;
	void render() override;
	void unload() override;
public:
	Tetris::Board board1, board2;
	AI::Genetic_al g_a;
	AI::Tree ai_1;
	AI::Tree ai_2;

	int po_size = 4;
	int pair_index = 0;
	std::vector<int> loser_index;
};

