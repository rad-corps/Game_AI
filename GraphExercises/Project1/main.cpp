
#include "Game1.h"


int main(int argc, char **argv)
{
	Game1 *pGame = new Game1(768, 768, false, "Game1");
	pGame->RunGame();
	delete pGame;

	return 0;
};