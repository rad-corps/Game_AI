#include "Game1.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Vector.h"
#include <iostream>
Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) : Application(windowWidth, windowHeight, fullscreen, title)
{
	m_spritebatch = SpriteBatch::Factory::Create(this, SpriteBatch::GL3);
	box = new Texture("./Images/nodeTexture.png");

	pGraph = new DirectedGraph();
	 Node *a = pGraph->AddNode(Vector2(100, 100));
	 Node *b = pGraph->AddNode(Vector2(150, 100));
	 Node *c = pGraph->AddNode(Vector2(200, 100));
	 Node *d = pGraph->AddNode(Vector2(150, 150));
	 Node *e = pGraph->AddNode(Vector2(100, 200));
	 Node *f = pGraph->AddNode(Vector2(150, 200));
	 Node *g = pGraph->AddNode(Vector2(200, 200));
	 Node *h = pGraph->AddNode(Vector2(300, 150));
	 Node *i = pGraph->AddNode(Vector2(250, 100));
	 Node *j = pGraph->AddNode(Vector2(300, 100));
	 Node *k = pGraph->AddNode(Vector2(350, 100));
	 pGraph->ConnectNodes(a, d, 1);
	 pGraph->ConnectNodes(b, d, 1);
	 pGraph->ConnectNodes(c, d, 1);
	 pGraph->ConnectNodes(d, h, 1);
	 pGraph->ConnectNodes(d, e, 1);
	 pGraph->ConnectNodes(d, f, 1);
	 pGraph->ConnectNodes(d, g, 1);
	 pGraph->ConnectNodes(i, h, 1);
	 pGraph->ConnectNodes(j, h, 1);
	 pGraph->ConnectNodes(k, h, 1);

	 std::cout << pGraph->ToString();

}

Game1::~Game1()
{
	SpriteBatch::Factory::Destroy(m_spritebatch);
	delete pGraph;
}


void Game1::Update(float deltaTime)
{

}

void Game1::Draw()
{
	// clear the back buffer
	ClearScreen();

	m_spritebatch->Begin();

	//get the nodes
	for (int i = 0; i < pGraph->size(); ++i)
	{
		Node* node = (*pGraph)[i];
		NodeData data = node->GetData();
		m_spritebatch->DrawSprite(box, data.pos.x, data.pos.y);

		//get the edge
		for (Edge edge : node->GetEdges())
		{
			//draw line from this node to edge
			Node* startNode = node;
			Node* endNode = edge.End();

			m_spritebatch->DrawLine(startNode->GetData().pos.x, startNode->GetData().pos.y, endNode->GetData().pos.x, endNode->GetData().pos.y);
		}
	}	

	m_spritebatch->End();

}