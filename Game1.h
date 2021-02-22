#pragma once

#include "Game.h"
#include "Tree.h"

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
	AI::Tree ai;
};

