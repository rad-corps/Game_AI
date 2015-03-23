
/*-----------------------------------------------------------------------------
Author:			
Description:	
-----------------------------------------------------------------------------*/
#ifndef GAME1_H
#define GAME1_H

#include "Application.h"
#include "Graph.h"
#include "PathFinder.h"
#include "Input.h"
#include <thread>
#include "Renderer.h"

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
	Graph *graph;
	PathFinder *pathFinder;
	Input* input;

private:

	void ThreadMain();
	std::thread searchThread;
	bool isRunning;
	bool bidirectional;
	Font *font;

	NodeRenderData nodeRenderData;
	std::vector<Node*> path;
	Renderer* renderer;
};

#endif