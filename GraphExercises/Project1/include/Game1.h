
/*-----------------------------------------------------------------------------
Author:			
Description:	
-----------------------------------------------------------------------------*/
#ifndef GAME1_H
#define GAME1_H

#include "Application.h"
#include "Graph.h"
#include "Input.h"
#include <thread>

class SpriteBatch;

class Game1 : public Application
{
public:

	// assets loaded in constructor
	Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title);

	// assets destroyed in destructor
	virtual ~Game1();

	// update / draw called each frame automaticly
	virtual void Update(float deltaTime);
	virtual void Draw();

protected:

	SpriteBatch *spritebatch;
	DirectedGraph *graph;
	Input* input;

private:

	void ThreadMain();
	std::thread updateThread;
	bool isRunning;
	bool bidirectional;
	Font *font;
};

#endif