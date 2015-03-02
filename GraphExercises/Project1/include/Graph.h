#pragma once

#include "Node.h"
#include "Edge.h"
#include <vector>
#include <string>
#include "Vector.h"
#include "SpriteBatch.h"
#include "Texture.h"

class DirectedGraph
{
public:
	DirectedGraph(void);
	~DirectedGraph(void);

	Node* AddNode(NodeData data_);
	Node* AddNode(Vector2 data_);
	Node* FindNode(Vector2 pos_, int tollerance_);
	std::vector<Node*> FindNodes(Vector2 pos_, int tollerance_);
	
	void RemoveNode(Node* node_);
	void RemoveNodeIf(Vector2 pos_, int tollerance_);
	void SetStartNode(Vector2 pos_, int tollerance_);
	void SetEndNode(Vector2 pos_, int tollerance_);
	
	Node* operator[](int index_);
	void ConnectNodes(Node* nodeA_, Node* nodeB_, EdgeData edgeData_);
	void ConnectNodes(Node* nodeA_, Node* nodeB_, int cose_);
	void ConnectCloseNodes(Node* nodeA_, int distance_);
	int size();
	void Draw(SpriteBatch* spriteBatch_);

	std::string ToString();

private:
	Node* startNode;
	Node* endNode;

	std::vector<Node*> graphData;
	static int nodeID;
	Texture* nodeSprite;
};