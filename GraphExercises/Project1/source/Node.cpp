#include "Node.h"
#include <sstream>
#include <algorithm>

Node::Node() : parent(nullptr), g(0) {}

Node::~Node(void){}

//sort based on gScore
bool Node::operator < (Node& node_)
{
	return f < node_.f;
}

void
Node::AddEdge(Node* end_, int cost_)
{	
	edges.push_back(Edge(end_, cost_));
}

void Node::RemoveEdgeIf(Node* node_)
{
	edges.erase( std::remove_if(edges.begin(), edges.end(), [node_](Edge& edge_) { return edge_.end == node_; } ) , edges.end() );
}

std::string
Node::ToString()
{
	std::stringstream ret;
	ret << "Node at: " << pos << " has " << edges.size() << " edges " << std::endl;
	
	for ( auto &edge : edges ) 
	{
		Node* tempNode = edge.end;
		ret << "Node at: " << pos << " is connected to Node at: " << pos << " cost: " << edge.cost << std::endl;
	}

	return ret.str();
}