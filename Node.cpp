#include "Node.h"

AI::Node::Node()
{
	this->parent = nullptr;
}

AI::Node::~Node()
{
}

/*void AI::Node::freeChildren()
{
	if (this->children.size() < 1) {
		// do nothing
	}
	else {
		for (int i = this->children.size() - 1; i >= 0; i--) {
			this->children[i]->freeChildren();
			delete this->children[i]; // maybe safe, maybe dangerous, don't know
			this->children.pop_back();
		}
	}
}
*/