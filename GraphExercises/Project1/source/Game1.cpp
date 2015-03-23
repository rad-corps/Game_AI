#include "Game1.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Vector.h"
#include <iostream>
#include <chrono>
#include <stdlib.h>//srand rand
#include <time.h>


using namespace std;

void Game1::ThreadMain()
{
	pathReady = false;
	path = pathFinder->AStar(*graph, nodeRenderData);
	pathReady = true;
}

Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) : Application(windowWidth, windowHeight, fullscreen, title)
{
	srand(time(NULL));
	nodeRenderData.currentNode = nullptr;
//	nodeRenderData.endNode = nullptr;
//	nodeRenderData.beginNode = nullptr;
	spritebatch = SpriteBatch::Factory::Create(this, SpriteBatch::GL3);
	input = Input::GetSingleton();	
	graph = new Graph();
	pathFinder = new PathFinder();
	font = new Font("./Fonts/arial_20px.fnt");
	bidirectional = true;
	renderer = new Renderer(spritebatch);
	pathReady = false;
	RegenerateNodes();
	pathReady = false;
}

Game1::~Game1()
{
	SpriteBatch::Factory::Destroy(spritebatch);
	delete graph;
}

void Game1::RegenerateNodes()
{
	graph->Clear();
	//create 50 random nodes between 0 and 760
	for (int i = 0; i < 40; ++i)
	{
		Node* node = graph->AddNode(Vector2(rand() % 760, rand() % 760));
		graph->ConnectCloseNodes(node, 200, bidirectional);
	}
}

void Game1::Update(float deltaTime)
{
	//get the mouse position
	int x, y;
	input->GetMouseXY(&x, &y);	
	Vector2 mousePos(x,y);

	//add a node where the mouse was clicked
	if (input->WasMouseButtonPressed(0))
	{
		Node* node = graph->AddNode(mousePos);
		graph->ConnectCloseNodes(node, 100, bidirectional);
	}

	if (input->WasMouseButtonPressed(1))
		graph->RemoveNodeIf(mousePos, 8); //8 is the radius of the node image		
	
	if (input->WasKeyPressed(GLFW_KEY_S))
		graph->SetStartNode(mousePos, 8);
	
	if (input->WasKeyPressed(GLFW_KEY_E))
		graph->SetEndNode(mousePos, 8);
	
//	if (input->WasKeyPressed(GLFW_KEY_D))
//		graph->DFS_Step();
	
//	if (input->WasKeyPressed(GLFW_KEY_B))
//		graph->BFS_Step();
	
	if (input->WasKeyPressed(GLFW_KEY_I))
	{
		std::vector<Node*> nodes = pathFinder->Dijkstras(*graph);
		graph->SetHilightedNodes(nodes);
	}

	if (input->WasKeyPressed(GLFW_KEY_J))
	{
		std::vector<Node*> nodes = pathFinder->Dijkstras2(*graph);
		graph->SetHilightedNodes(nodes);
	}

	if (input->WasKeyPressed(GLFW_KEY_A))
	{
		searchThread = std::thread(&Game1::ThreadMain, this);		
	}

	
	if (input->WasKeyPressed(GLFW_KEY_O))
		cout << graph->ToString() << endl;

	if (input->WasKeyPressed(GLFW_KEY_1))
		bidirectional = !bidirectional;

	if (input->WasKeyPressed(GLFW_KEY_C))
		graph->PrepareForSearch();
	
	if (input->WasKeyPressed(GLFW_KEY_1))
		graph->Clear();
	
	if (input->WasKeyPressed(GLFW_KEY_2))
		RegenerateNodes();
	
}

void Game1::Draw()
{
	// clear the back buffer
	ClearScreen();

	spritebatch->Begin();

	graph->Draw(spritebatch, font);

	spritebatch->SetRenderColor(255, 255, 255, 255);
	
	spritebatch->DrawString(font, "S - Set start node", 10, 10);
	spritebatch->DrawString(font, "E - Set end node", 10, 30);	
	spritebatch->DrawString(font, "B - Breadth first search step", 10, 50);
	spritebatch->DrawString(font, "D - Depth first search step", 10, 70);
	spritebatch->DrawString(font, "I - Dijkstra's algorithm search", 10, 90);
	spritebatch->DrawString(font, "J - Dijkstra's 2 algorithm search", 10, 110);
	spritebatch->DrawString(font, "O - Output graph data to console", 10, 130);
	spritebatch->DrawString(font, "1 - Toggle Bidirectional/Directional", 10, 150);
	bidirectional ? spritebatch->DrawString(font, "Bidirectional", 10, 170) : spritebatch->DrawString(font, "Directional", 10, 150);
	spritebatch->DrawString(font, "C - Clear Search Data", 10, 190);
	
	spritebatch->DrawString(font, "A - Perform A Star Search", 10, 210);
	spritebatch->DrawString(font, "1 - Clear Graph", 10, 230);
	spritebatch->DrawString(font, "2 - Regenerate Random Graph", 10, 250);

	renderer->Draw(graph->GraphData(), 0, 0, 255, 255);
	renderer->Draw(nodeRenderData.openList, 255, 0, 0, 255);
	renderer->Draw(nodeRenderData.closedList, 0, 255, 0, 255);	
	renderer->Draw(graph->StartNode(), 255, 255, 0, 255);
	renderer->Draw(graph->EndNode(), 0, 255, 255, 255);
	renderer->Draw(nodeRenderData.currentNode, 255, 255, 255, 255);

	if (pathReady)
	{
		renderer->Draw(path, 255, 255, 255, 255);
	}

	spritebatch->End();

}