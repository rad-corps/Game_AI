#include "Game1.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Vector.h"
#include <iostream>
#include <chrono>


using namespace std;

void Game1::ThreadMain()
{
	while (true)
	{
		graph->DFS_Step();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) : Application(windowWidth, windowHeight, fullscreen, title)
{

	spritebatch = SpriteBatch::Factory::Create(this, SpriteBatch::GL3);
	input = Input::GetSingleton();	
	graph = new Graph();
	pathFinder = new PathFinder();
	font = new Font("./Fonts/arial_20px.fnt");
	bidirectional = true;
}

Game1::~Game1()
{
	SpriteBatch::Factory::Destroy(spritebatch);
	delete graph;
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
		graph->DFS_Step();
	
	if (input->WasKeyPressed(GLFW_KEY_B))
		graph->BFS_Step();
	
	if (input->WasKeyPressed(GLFW_KEY_I))
	{
		std::vector<Node*> nodes = pathFinder->Dijkstras(*graph);
		graph->SetHilightedNodes(nodes);
	}
	
	if (input->WasKeyPressed(GLFW_KEY_O))
		cout << graph->ToString() << endl;

	if (input->WasKeyPressed(GLFW_KEY_1))
		bidirectional = !bidirectional;

	if (input->WasKeyPressed(GLFW_KEY_C))
		graph->PrepareForSearch();
	
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
	spritebatch->DrawString(font, "O - Output graph data to console", 10, 110);
	spritebatch->DrawString(font, "1 - Toggle Bidirectional/Directional", 10, 130);
	bidirectional ? spritebatch->DrawString(font, "Bidirectional", 10, 150) : spritebatch->DrawString(font, "Directional", 10, 150);
	spritebatch->DrawString(font, "C - Clear Search Data", 10, 170);

	spritebatch->End();

}