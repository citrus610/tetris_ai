#include "Game1.h"

void Game1::load()
{
	this->board1.setPosScale(80, 140, 40);
	this->board2.setPosScale(80 + 1920 / 2, 140, 40);
	this->board1.setEnemy(&this->board2);
	this->board2.setEnemy(&this->board1);
	this->board1.init();
	this->board2.init();
	this->board2.enableAI();

	this->ai.setRootState(this->board2.data, this->board2.currentPiece, this->board2.holdPiece, this->board2.nextPiece, false, 0);
}

void Game1::update(float dt)
{
	std::string move2 = this->ai.findMove(this->board2.data);
	///*
	for (int i = 0; i < (int)move2.length(); i++) {
		switch (move2[i])
		{
		case 'L':
			this->board2.realCurrentPiece.tryLeft(this->board2.data);
			break;
		case 'R':
			this->board2.realCurrentPiece.tryRight(this->board2.data);
			break;
		case 'C':
			this->board2.hold();
			break;
		case 'X':
			this->board2.realCurrentPiece.tryRotate(1, this->board2.data);
			break;
		case 'Z':
			this->board2.realCurrentPiece.tryRotate(3, this->board2.data);
			break;
		case 'H':
			this->board2.realCurrentPiece.tryHardDrop(this->board2.data);
			break;
		case 'S':
			this->board2.realCurrentPiece.tryHardDrop(this->board2.data);
			break;
		default:
			break;
		}
	}//*/

	this->board1.update(dt);
	this->board2.update(dt);
	if (this->board1.isGameover() || this->board2.isGameover()) {
		this->board1.init();
		this->board2.init();
		this->ai.deleteNode(this->ai.root);
		this->ai.root = new AI::Node;
		this->ai.setRootState(this->board2.data, this->board2.currentPiece, this->board2.holdPiece, this->board2.nextPiece, false, 0);
	}

	this->ai.addPiece(this->ai.root, this->board2.nextPiece[4]);
}

void Game1::render()
{
	this->canvas.clear();
	this->board1.render(&this->canvas);
	this->board2.render(&this->canvas);
}

void Game1::unload()
{
}
