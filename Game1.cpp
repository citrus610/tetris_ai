#include "Game1.h"

void Game1::load()
{
	this->board1.setPosScale(80, 140, 40);
	this->board2.setPosScale(80 + 1920 / 2, 140, 40);
	this->board1.setEnemy(&this->board2);
	this->board2.setEnemy(&this->board1);
	this->board1.init();
	this->board2.init();
	this->board1.enableAI();
	this->board2.enableAI();

	this->ai_1.setRootState(this->board1.data, this->board1.currentPiece, this->board1.holdPiece, this->board1.nextPiece, false, 0);
	this->ai_2.setRootState(this->board2.data, this->board2.currentPiece, this->board2.holdPiece, this->board2.nextPiece, false, 0);

	///*
	this->g_a.init(this->po_size);
	//this->g_a.save();

	this->ai_1.evaluator.weights = this->g_a.population[0];
	this->ai_2.evaluator.weights = this->g_a.population[1];
	//*/
}

void Game1::update(float dt)
{
	///*
	if (this->board1.lineClearDelayTimer >= 0.5f) {
		std::string move1 = this->ai_1.findMove(this->board1.data, this->board1.currentPiece, this->board1.holdPiece, this->board1.nextPiece, this->board1.isB2bReady, this->board1.ren);
		for (int i = 0; i < (int)move1.length(); i++) {
			switch (move1[i])
			{
			case 'L':
				this->board1.realCurrentPiece.tryLeft(this->board1.data);
				break;
			case 'R':
				this->board1.realCurrentPiece.tryRight(this->board1.data);
				break;
			case 'C':
				this->board1.hold();
				break;
			case 'X':
				this->board1.realCurrentPiece.tryRotate(1, this->board1.data);
				break;
			case 'Z':
				this->board1.realCurrentPiece.tryRotate(3, this->board1.data);
				break;
			case 'H':
				this->board1.realCurrentPiece.tryHardDrop(this->board1.data);
				break;
			case 'S':
				this->board1.realCurrentPiece.tryHardDrop(this->board1.data);
				break;
			default:
				break;
			}
		}
	}//*/
	///*
	if (this->board2.lineClearDelayTimer >= 0.5f) {
		std::string move2 = this->ai_2.findMove(this->board2.data, this->board2.currentPiece, this->board2.holdPiece, this->board2.nextPiece, this->board2.isB2bReady, this->board2.ren);
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
		}
	}//*/
	this->board1.update(dt);
	this->board2.update(dt);
	if (this->board1.isGameover() || this->board2.isGameover()) {
		///*
		if (this->board1.isGameover()) {
			this->loser_index.push_back(this->pair_index * 2);
		}
		else {
			this->loser_index.push_back(this->pair_index * 2 + 1);
		}//*/

		this->board1.init();
		this->board2.init();
		this->ai_1.reset(this->board1.data, this->board1.currentPiece, this->board1.holdPiece, this->board1.nextPiece, false, 0);
		this->ai_2.reset(this->board2.data, this->board2.currentPiece, this->board2.holdPiece, this->board2.nextPiece, false, 0);

		///*
		this->pair_index++;
		if (pair_index * 2 + 1 < this->po_size) {
			this->ai_1.evaluator.weights = this->g_a.population[pair_index * 2];
			this->ai_2.evaluator.weights = this->g_a.population[pair_index * 2 + 1];
		}
		else {
			// delete loser
			for (int i = this->loser_index.size() - 1; i >= 0; i--) {
				this->g_a.population.erase(this->g_a.population.begin() + this->loser_index[i]);
			}

			// mutate winner
			for (int i = 0; i < this->po_size / 4; i++) {
				this->g_a.population.push_back(this->g_a.mutate(this->g_a.population[i * 2], this->g_a.population[i * 2 + 1]));
			}
			this->g_a.population.push_back(this->g_a.mutate(this->g_a.population[0], this->g_a.population[this->po_size / 2 - 1]));

			// save weight
			this->g_a.save();

			this->end();
		}//*/
	}
};

void Game1::render()
{
	this->canvas.clear();
	this->board1.render(&this->canvas);
	this->board2.render(&this->canvas);
};

void Game1::unload()
{
};
