#pragma once

#include <vector>
#include <string>
#include "Edge.h"
#include "Vector.h"

struct NodeData
{
	int nodeID;
	Vector2 pos;
	bool traversed;
	int gScore;
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
	void SetGScore(int gScore_);
	void SetParent(Node* parent_);
	Node* GetParent();

	bool operator < (Node& node_);
private:
	Node* parent;
	NodeData data;
	std::vector<Edge> edges;
};

