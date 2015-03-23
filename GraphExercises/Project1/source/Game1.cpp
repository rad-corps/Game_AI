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
#include <sstream>


using namespace std;

void Game1::AStarThread()
{
	path = pathFinder->AStar(*graph, nodeRenderData, speed);
	threadRunning = false;
}
void Game1::DijkstrasThread()
{
	path = pathFinder->Dijkstras(*graph, nodeRenderData, speed);
	threadRunning = false;
}
void Game1::DFSThread()
{
	path = pathFinder->DFS(*graph, nodeRenderData, speed);
	threadRunning = false;
}
void Game1::BFSThread()
{
	path = pathFinder->BFS(*graph, nodeRenderData, speed);
	threadRunning = false;
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
	threadRunning = false;
	RegenerateNodes();
	speed = 100;
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
	
	if (input->WasKeyPressed(GLFW_KEY_D))
	{
		if (graph->StartNode() != nullptr && graph->EndNode() != nullptr && !threadRunning)
		{
			threadRunning = true;
			searchThread = std::thread(&Game1::DFSThread, this);
		}
	}
	
	if (input->WasKeyPressed(GLFW_KEY_B))
	{
		if (graph->StartNode() != nullptr && graph->EndNode() != nullptr && !threadRunning)
		{
			threadRunning = true;
			searchThread = std::thread(&Game1::BFSThread, this);
		}
	}
	
	if (input->WasKeyPressed(GLFW_KEY_I))
	{		
		if (graph->StartNode() != nullptr && graph->EndNode() != nullptr && !threadRunning)
		{
			threadRunning = true;
			searchThread = std::thread(&Game1::DijkstrasThread, this);
		}
	}

	if (input->WasKeyPressed(GLFW_KEY_A))
	{
		if (graph->StartNode() != nullptr && graph->EndNode() != nullptr && !threadRunning)
		{
			threadRunning = true;
			searchThread = std::thread(&Game1::AStarThread, this);
		}
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
	
	if (input->WasKeyPressed(GLFW_KEY_2))
	{
		RegenerateNodes();
		nodeRenderData.Clear();
		path.clear();
	}

	if (input->WasKeyPressed(GLFW_KEY_3))
	{
		graph->Clear();
		nodeRenderData.Clear();
		path.clear();
	}

	if (input->WasKeyPressed(GLFW_KEY_4))
	{
		speed *= 2;
		if (speed > 2000) speed = 100;
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
	bidirectional ? DrawText("T - Bidirectional On") : DrawText("T - Directional On");
	DrawText("1 - Clear Search Data");
	DrawText("2 - Regenerate Random Graph");
	DrawText("3 - Remove Graph");
	stringstream speedStr;
	speedStr << "4 - Speed " << speed;
	DrawText(speedStr.str());
	

	renderer->Draw(graph->GraphData(), 0, 0, 255, 255);
	renderer->Draw(nodeRenderData.openList, 255, 0, 0, 255);
	renderer->Draw(nodeRenderData.closedList, 0, 255, 0, 255);	
	renderer->Draw(graph->StartNode(), 255, 150, 0, 255);
	renderer->Draw(graph->EndNode(), 255, 0, 255, 255);
	renderer->Draw(nodeRenderData.currentNode, 255, 255, 255, 255);


	if (!threadRunning && searchThread.joinable())
	{
		searchThread.join();		
	}
	if (!threadRunning)
	{
		renderer->Draw(path, 255, 255, 255, 255);
	}

	spritebatch->End();

}