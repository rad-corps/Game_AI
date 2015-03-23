
#include "Game1.h"


int main(int argc, char **argv)
{
	////benchmarking code
	//auto start_time = std::chrono::high_resolution_clock::now();
	//auto end_time = std::chrono::high_resolution_clock::now();
	//auto time = end_time - start_time;
	//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << endl;


	Game1 *pGame = new Game1(768, 768, false, "Game1");
	pGame->RunGame();
	delete pGame;

	return 0;
};