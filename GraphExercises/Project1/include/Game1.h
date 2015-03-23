
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
#include <atomic>
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
	void RegenerateNodes();
	Vector2 GenRandVector();
	void DrawText(std::string text_);

protected:

	SpriteBatch *spritebatch;
	Graph *graph;
	PathFinder *pathFinder;
	Input* input;

private:
	int yText;
	void AStarThread();
	void DijkstrasThread();
	void DFSThread();
	void BFSThread();
	std::thread searchThread;
	bool bidirectional;
	Font *font;
	std::atomic<bool> threadRunning;

	NodeRenderData nodeRenderData;
	std::vector<Node*> path;
	Renderer* renderer;
	int speed;
};

#endif