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
	
	graph = new DirectedGraph();
	//Node *a = graph->AddNode(Vector2(100, 100));
	//Node *b = graph->AddNode(Vector2(150, 100));
	//Node *c = graph->AddNode(Vector2(200, 100));
	//Node *d = graph->AddNode(Vector2(150, 150));
	//Node *e = graph->AddNode(Vector2(100, 200));
	//Node *f = graph->AddNode(Vector2(150, 200));
	//Node *g = graph->AddNode(Vector2(200, 200));
	//Node *h = graph->AddNode(Vector2(300, 150));
	//Node *i = graph->AddNode(Vector2(250, 100));
	//Node *j = graph->AddNode(Vector2(300, 100));
	//Node *k = graph->AddNode(Vector2(350, 100));

	//graph->ConnectNodes(a, d, 1);
	//graph->ConnectNodes(b, d, 1);
	//graph->ConnectNodes(c, d, 1);
	//graph->ConnectNodes(d, h, 1);
	//graph->ConnectNodes(d, e, 1);
	//graph->ConnectNodes(d, f, 1);
	//graph->ConnectNodes(d, g, 1);
	//graph->ConnectNodes(i, h, 1);
	//graph->ConnectNodes(j, h, 1);
	//graph->ConnectNodes(k, h, 1);

	//std::cout << graph->ToString();

	font = new Font("./Fonts/arial_20px.fnt");

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
		graph->ConnectCloseNodes(node, 100);
	}

	if (input->WasMouseButtonPressed(1))
	{
		graph->RemoveNodeIf(mousePos, 8); //8 is the radius of the node image		
	}

	if (input->WasKeyPressed(GLFW_KEY_S))
	{
		graph->SetStartNode(mousePos, 8);
	}
	if (input->WasKeyPressed(GLFW_KEY_E))
	{
		graph->SetEndNode(mousePos, 8);
	}
	if (input->WasKeyPressed(GLFW_KEY_D))
	{
		//updateThread = std::thread(&Game1::ThreadMain, this);
		graph->DFS_Step();
	}
	if (input->WasKeyPressed(GLFW_KEY_B))
	{
		graph->BFS_Step();
	}
	if (input->WasKeyPressed(GLFW_KEY_I))
	{
		graph->Dijkstra_Step();
	}
	if (input->WasKeyPressed(GLFW_KEY_O))
	{
		cout << graph->ToString() << endl;
	}

}

void Game1::Draw()
{
	// clear the back buffer
	ClearScreen();

	spritebatch->Begin();

	graph->Draw(spritebatch);

	spritebatch->SetRenderColor(255, 255, 255, 255);
	
	spritebatch->DrawString(font, "S - Set start node", 10, 10);
	spritebatch->DrawString(font, "E - Set end node", 10, 25);
	spritebatch->DrawString(font, "B - Breadth first search step", 10, 40);
	spritebatch->DrawString(font, "D - Depth first search step", 10, 55);
	spritebatch->DrawString(font, "I - Dijkstra's algorithm search step", 10, 70);
	spritebatch->DrawString(font, "O - Output graph data to console", 10, 85);

	spritebatch->End();

}