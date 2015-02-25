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
	void RemoveNode(Node* node_);
	Node* operator[](int index_);
	void ConnectNodes(Node* nodeA_, Node* nodeB_, EdgeData edgeData_);
	void ConnectNodes(Node* nodeA_, Node* nodeB_, int cose_);
	int size();
	void Draw(SpriteBatch* spriteBatch_);

	std::string ToString();

private:
	std::vector<Node*> graphData;
	static int nodeID;
	Texture* nodeSprite;
};