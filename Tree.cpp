#include "Tree.h"

AI::Tree::Tree()
{
	this->root = new Node;
}

AI::Tree::~Tree()
{
	this->deleteNode(this->root);
}

float AI::Tree::getUBC(Node* _node)
{
	float result = 0;
	if (this->root->visit == 0 || _node->visit == 0)
		return -999.0f;
	float c = std::sqrt(2);
	result = _node->score / _node->visit + c * std::sqrt(std::log(this->root->visit) / _node->visit);
	return 0.0f;
}

AI::Node* AI::Tree::getBestChild(Node* _node)
{
	if (_node->children.size() == 0) {
		return nullptr;
	}
	else {

		for (int i = 0; i < (int)_node->children.size(); i++) {
			if (_node->children[i]->visit == 0)
				return _node->children[i];
		} // if a child hadn't been visited yet, return it

		int index = 0;
		while (index < (int)_node->children.size() && this->isUnexpandable(_node->children[index])) // find the index of the child which is expandable (there is next piece available)
		{
			index++;
		}
		if (index == (int)_node->children.size()) { // if there is no expandable child, return null
			return nullptr;
		}
		if (index + 1 == (int)_node->children.size()) { // if there is only one child that is expandable, return it
			return _node->children[index];
		}
		for (int i = index + 1; i < (int)_node->children.size(); i++) { // compare children's UBC score to get the child with highest score
			if (!this->isUnexpandable(_node->children[i]) && this->getUBC(_node->children[i]) > this->getUBC(_node->children[index])) {
				index = i;
			}
		}
		return _node->children[index];
	}
}

void AI::Tree::backpropagate(Node* _node)
{
	if (_node != this->root) {
		_node->parent->score += _node->score;
		_node->parent->visit++;
		this->backpropagate(_node->parent);
	}
}

bool AI::Tree::isUnexpandable(Node* _node)
{
	if (_node->unexpandable && _node->visit > 0)
		return true;
	if (_node->children.size() > 0) {
		int sum = 0;
		for (int i = 0; i < (int)_node->children.size(); i++) {
			if (this->isUnexpandable(_node->children[i]))
				sum++;
		}
		if (sum == _node->children.size()) {
			_node->unexpandable = true;
			return true;
		}
		else {
			_node->unexpandable = false;
		}
	}
	return false;
}

void AI::Tree::setRootState(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::vector<char> next, bool b2b, int ren)
{
	this->root->board = AI::Bot_Board::encodeData(_board_data);
	this->root->current = current;
	this->root->hold = hold;
	std::string _next_pieces;
	for (int i = 0; i < (int)next.size(); i++) {
		_next_pieces.push_back(next[i]);
	}
	this->root->next = _next_pieces;
	this->root->b2b = b2b;
	this->root->ren = ren;
}

void AI::Tree::setRootState(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::string next, bool b2b, int ren)
{
	this->root->board = AI::Bot_Board::encodeData(_board_data);
	this->root->current = current;
	this->root->hold = hold;
	this->root->next = next;
	this->root->b2b = b2b;
	this->root->ren = ren;
}

void AI::Tree::addPiece(Node* _node, char _piece)
{
	_node->next.push_back(_piece);
	if (_node->children.size() > 0) {
		for (int i = 0; i < (int)_node->children.size(); i++) {
			this->addPiece(_node->children[i], _piece);
		}
	}
}

void AI::Tree::shiftNext(int index)
{
	//this->root = this->root->children[index];

	// delete all other children
	for (int i = 0; i < (int)this->root->children.size(); i++) {
		if (i != index) {
			this->deleteNode(this->root->children[i]);
		}
	}

	// store the "next" node
	Node* new_root = this->root->children[index];

	// change the root
	delete this->root;
	this->root = new_root;
}

void AI::Tree::reset(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::vector<char> next, bool b2b, int ren)
{
	this->deleteNode(this->root);
	this->root = new Node;
	this->setRootState(_board_data, current, hold, next, b2b, ren);
}

void AI::Tree::reset(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::string next, bool b2b, int ren)
{
	this->deleteNode(this->root);
	this->root = new Node;
	this->setRootState(_board_data, current, hold, next, b2b, ren);
}

void AI::Tree::deleteNode(Node * _node)
{
	if (_node->children.size() > 0) {
		for (int i = 0; i < (int)_node->children.size(); i++) {
			this->deleteNode(_node->children[i]);
		}
	}
	delete _node;
}

std::string AI::Tree::findMove(std::array<std::array<int, 10>, 40> _board_data)
{
	std::string real_current_board = AI::Bot_Board::encodeData(_board_data);

	if (this->root->children.size() == 0) {
		this->generator.expand(this->root);
	}
	else {
		if (real_current_board != this->root->board) {
			this->reset(_board_data, this->root->current, this->root->hold, this->root->next, this->root->b2b, this->root->ren);
			this->generator.expand(this->root);
		}
	}

	this->root->visit = 0;

	/*
	// MCTS
	while (this->root->visit < 50)
	{
		// selection
		Node* leaf_node = this->root;
		while (leaf_node->children.size() > 0)
		{
			leaf_node = this->getBestChild(leaf_node);
		}

		// expansion
		if (leaf_node->visit == 0) {
			leaf_node->score = this->evaluator.evaluate(leaf_node);
			leaf_node->visit = 1;
		}
		else {
			this->generator.expand(leaf_node);
			leaf_node = this->getBestChild(leaf_node);
			leaf_node->score = this->evaluator.evaluate(leaf_node);
			leaf_node->visit = 1;
		}

		// backpropagate
		this->backpropagate(leaf_node);
	}

	// find best path
	int best_index = 0;
	for (int i = 1; i < (int)this->root->children.size(); i++) {
		if (this->root->children[i]->visit > this->root->children[best_index]->visit) {
			best_index = i;
		}
	}


	//*/
	// find best path
	for (int i = 1; i < (int)this->root->children.size(); i++) {
		this->root->children[i]->score = this->evaluator.evaluate(this->root->children[i]);
		std::cout << this->root->children[i]->score << " ";
	}
	std::cout << "\n";
	int best_index = 0;
	for (int i = 1; i < (int)this->root->children.size(); i++) {
		if (this->root->children[i]->score > this->root->children[best_index]->score) {
			best_index = i;
		}
	}

	this->shiftNext(best_index);

	return this->root->path;
}
