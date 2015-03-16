#include "Graph.h"
#include "Node.h"
#include <vector>
#include <map>

class NodePathFinderData
{
public:
	Node* node;
	Node* parent;
	int gScore;

	bool operator < (NodePathFinderData& npfd_)
	{
		return this->gScore < npfd_.gScore;
	}
	bool operator == (NodePathFinderData node_)
	{
		return this->node == node_.node;
	}
};

#pragma once
class PathFinder
{
public:
	PathFinder();
	~PathFinder();

	std::vector<Node*> Dijkstras(Graph& graph_);

private:



	

};

