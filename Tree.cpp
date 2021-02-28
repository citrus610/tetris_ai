#include "Tree.h"

AI::Tree::Tree()
{
	this->root = std::make_shared<Node>();
}

AI::Tree::~Tree()
{
	//this->deleteNode(this->root);
}

float AI::Tree::getUBC(std::shared_ptr<Node> _node)
{
	float result = 0;
	if (this->root->visit == 0 || _node->visit == 0)
		return -999.0f;
	float c = 2;
	result = _node->score / _node->visit + c * std::sqrt(std::log(this->root->visit) / _node->visit);
	return result;
}

std::shared_ptr<AI::Node> AI::Tree::getBestChild(std::shared_ptr<Node>_node)
{
	if (_node->children.size() == 0) {
		std::cout << "1" << "\n";
		return nullptr;
	}/*
	else if (this->isUnexpandable(_node)) {
		std::cout << "2" << "\n";
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
			std::cout << "3" << "\n";
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
	int index = 0;
	for (int i = 1; i < (int)_node->children.size(); i++) {
		if (this->isUnexpandable(_node->children[i])) {
			continue;
		}
		if (this->getUBC(_node->children[i]) > this->getUBC(_node->children[index])) {
			index = i;
		}
	}
	return _node->children[index];*/

	for (int i = 0; i < (int)_node->children.size(); i++) {
		if (_node->children[i]->visit == 0)
			return _node->children[i];
	} // if a child hadn't been visited yet, return it

	int index = 0;
	for (int i = 1; i < (int)_node->children.size(); i++) {
		if (this->isUnexpandable(_node->children[i]) == false) {
			index = i;
			break;
		}
	}
	for (int i = index; i < (int)_node->children.size(); i++) {
		if (this->getUBC(_node->children[i]) > this->getUBC(_node->children[index])) {
			index = i;
		}
	}
	return _node->children[index];
}

void AI::Tree::backpropagate(std::shared_ptr<Node> _node)
{
	if (_node != this->root) {
		_node->parent.lock()->score += _node->score;
		_node->parent.lock()->visit++;
		this->backpropagate(_node->parent.lock());
	}
}

bool AI::Tree::isUnexpandable(std::shared_ptr<Node> _node)
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

void AI::Tree::reviveDead(std::shared_ptr<Node> _node)
{
	_node->unexpandable = false;
	for (int i = 0; i < (int)_node->children.size(); i++) {
		this->reviveDead(_node->children[i]);
	}
}

void AI::Tree::setRootState(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::string next, bool b2b, int ren)
{
	this->root->board = AI::Bot_Board::normalize(_board_data);
	this->root->current = current;
	this->root->hold = hold;
	std::vector<char> _next_pieces;
	for (int i = 0; i < (int)next.size(); i++) {
		_next_pieces.push_back(next[i]);
	}
	this->root->next = _next_pieces;
	this->root->b2b = b2b;
	this->root->ren = ren;
}

void AI::Tree::setRootState(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::vector<char> next, bool b2b, int ren)
{
	this->root->board = _board_data;
	this->root->current = current;
	this->root->hold = hold;
	this->root->next = next;
	this->root->b2b = b2b;
	this->root->ren = ren;
}

void AI::Tree::addPiece(std::shared_ptr<Node> _node, char _piece)
{
	if (_node->current == ' ')
		_node->current = _piece;
	else
		_node->next.push_back(_piece);
	if (_node->children.size() > 0) {
		for (int i = 0; i < (int)_node->children.size(); i++) {
			this->addPiece(_node->children[i], _piece);
		}
	}
}

void AI::Tree::shiftNext(int index)
{
	this->root = this->root->children[index];

	/*
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
	//*/
}

void AI::Tree::reset(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::vector<char> next, bool b2b, int ren)
{
	//this->deleteNode(this->root);
	this->root = std::make_shared<Node>();
	this->setRootState(_board_data, current, hold, next, b2b, ren);
}

void AI::Tree::reset(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::string next, bool b2b, int ren)
{
	//this->deleteNode(this->root);
	this->root = std::make_shared<Node>();
	this->setRootState(_board_data, current, hold, next, b2b, ren);
}

/*void AI::Tree::deleteNode(Node * _node)
{
	if (_node->children.size() > 0) {
		for (int i = 0; i < (int)_node->children.size(); i++) {
			this->deleteNode(_node->children[i]);
		}
	}
	delete _node;
}*/

std::string AI::Tree::findMove(std::array<std::array<int, 10>, 40> _board_data, char current, char hold, std::vector<char> next, bool b2b, int ren)
{
	std::cout << "new" << "\n";
	std::array<std::array<int, 10>, 40> real_board = AI::Bot_Board::normalize(_board_data);

	if (this->root->children.size() < 1) {
		this->generator.expand(this->root);
	}
	else {
		if (this->root->board == real_board) {
			this->reviveDead(this->root);
		}
		else {
			std::cout << "board changed" << "\n";
			this->reset(_board_data, current, hold, next, b2b, ren);
			this->generator.expand(this->root);
		}
	}

	while (this->root->visit < 400)
	{
		std::cout << "iter: " << (400 - this->root->visit) << "\n";
		s_board.setState(_board_data, current, hold, next, b2b, ren);

		// selection
		std::shared_ptr<Node> leaf = this->root;
		while (leaf->children.size() != 0)
		{
			leaf = this->getBestChild(leaf);
			this->s_board.attempt(leaf->path, leaf);
			//std::cout << "	children count	" << leaf->children.size() << "\n";
		}

		std::cout << "	leaf current	" << leaf->current << "\n";

		// expansion
		if (leaf->visit < 1) {
			//std::cout << "	no visit \n";
		}
		else {
			//std::cout << "	yes visit \n";
			this->generator.expand(leaf);
			leaf = this->getBestChild(leaf);
			this->s_board.attempt(leaf->path, leaf);
		}

		// evaluation
		leaf->score = this->evaluator.evaluate(leaf);
		leaf->visit = 1;

		// backpropagate
		this->backpropagate(leaf);
	}

	// find best move
	int index = 0;
	for (int i = 1; i < (int)this->root->children.size(); i++) {
		if (this->root->children[i]->visit > this->root->children[index]->visit) {
			index = i;
		}
	}

	this->shiftNext(index);

	return this->root->path;
}
