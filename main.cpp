#include <iostream>
#include <string>
#include "Game1.h"

int main()
{
	srand(time(NULL));

	Game1 game;

	game.start();

	/*int a = 69;

	int* p = &a;

	std::cout << p << "\n";*/

	/*
		Vector of pointer notice:
	- assuming we have: vector<A*> vector;
	- must use "delete" to free memory, for example: delete vector[i];
	- after that, must use "erase" at that location to avoid "hole" in vector: vector.erase(vector.begin() + i);
	*/

	return 0;
}