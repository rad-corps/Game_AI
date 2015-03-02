#pragma once

#include <vector>
#include <string>
#include "Edge.h"
#include "Vector.h"

struct NodeData
{
	int nodeID;
	//x/y coords go here
	Vector2 pos;
	bool traversed;
};

class Node
{
public:
	Node(NodeData nd_);
	~Node(void);
	void AddEdge(Node* end_, EdgeData data_);
	void RemoveEdgeIf(Node* edge_);
	NodeData GetData();
	std::vector<Edge> GetEdges();
	std::string ToString();
	void MarkAsTraversed(bool traversed_ = true);

private:
	NodeData data;
	std::vector<Edge> edges;
};

