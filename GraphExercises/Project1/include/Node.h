#pragma once

#include <vector>
#include <string>
#include "Edge.h"
#include "Vector.h"
struct Node
{
	//functions
	Node();
	~Node();
	void AddEdge(Node* end_, int cost_);
	void RemoveEdgeIf(Node* edge_);		
	std::string ToString();
	bool operator < (Node& node_);
	
	//members
	int g;
	int f; //g + h (h calculated, not stored)
	Node* parent;
	Vector2 pos;
	std::vector<Edge> edges;
};

