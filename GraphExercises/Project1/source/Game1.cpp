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
	font = new Font("./Fonts/CourierNew_11px.fnt");
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

Vector2 Game1::GenRandVector()
{
	Vector2 ret(rand() % 760, rand() % 760);
	if (ret.x < 300 && ret.y < 300)
		return GenRandVector();
	if (graph->NodeWithin(ret, 85))
		return GenRandVector();
	return ret;
}

void Game1::RegenerateNodes()
{
	graph->Clear();
	//create 50 random nodes between 0 and 760
	for (int i = 0; i < 30; ++i)
	{
		int x = rand() % 760;
		int y = rand() % 760;
		Node* node = graph->AddNode(GenRandVector());
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
		if (graph->StartNode() != nullptr && graph->EndNode() != nullptr)
			searchThread = std::thread(&Game1::ThreadMain, this);		
	}

	
	if (input->WasKeyPressed(GLFW_KEY_O))
		cout << graph->ToString() << endl;

	if (input->WasKeyPressed(GLFW_KEY_T))
		bidirectional = !bidirectional;

	if (input->WasKeyPressed(GLFW_KEY_1))
	{
		//graph->ClearStartAndEndNodes();
		nodeRenderData.Clear();
		path.clear();
	}
	
	if (input->WasKeyPressed(GLFW_KEY_3))
	{
		graph->Clear();
		nodeRenderData.Clear();
		path.clear();
	}
	
	if (input->WasKeyPressed(GLFW_KEY_2))
	{
		RegenerateNodes();
		nodeRenderData.Clear();
		path.clear();	
	}
	
}

void Game1::DrawText(std::string text_)
{
	spritebatch->DrawString(font, text_.c_str(), 10, yText);
	yText += 15;
}

void Game1::Draw()
{
	// clear the back buffer
	ClearScreen();

	spritebatch->Begin();

	graph->Draw(spritebatch, font);

	spritebatch->SetRenderColor(255, 255, 255, 255);
	
	yText = 10;
	DrawText("S - Set start node");
	DrawText("E - Set end node");
	DrawText("B - Breadth first search");
	DrawText("D - Depth first search");
	DrawText("I - Dijkstra's algorithm search");
	DrawText("A - Perform A Star Search");
	DrawText("O - Output graph data to console");
	DrawText("T - Toggle Bidirectional/Directional");
	bidirectional ? DrawText("Bidirectional") : DrawText("Directional");
	DrawText("1 - Clear Search Data");
	DrawText("2 - Regenerate Random Graph");
	DrawText("3 - Remove Graph");
	

	renderer->Draw(graph->GraphData(), 0, 0, 255, 255);
	renderer->Draw(nodeRenderData.openList, 255, 0, 0, 255);
	renderer->Draw(nodeRenderData.closedList, 0, 255, 0, 255);	
	renderer->Draw(graph->StartNode(), 255, 150, 0, 255);
	renderer->Draw(graph->EndNode(), 0, 255, 255, 255);
	renderer->Draw(nodeRenderData.currentNode, 255, 255, 255, 255);

	if (pathReady)
	{
		if (searchThread.joinable())
			searchThread.join();
		renderer->Draw(path, 255, 255, 255, 255);
	}

	spritebatch->End();

}