#include "Node.h"
#include <sstream>
#include <algorithm>

Node::Node(NodeData data_)
{
	data = data_;
}

Node::~Node(void)
{
}

NodeData
Node::GetData()
{
	return data;
}

std::vector<Edge> Node::GetEdges()
{
	return edges;
}


void
Node::AddEdge(Node* end_, EdgeData data_)
{	
	edges.push_back(Edge(end_, data_));
}

void Node::RemoveEdgeIf(Node* node_)
{
	edges.erase( std::remove_if(edges.begin(), edges.end(), [node_](Edge& edge_) { return edge_.End() == node_; } ) , edges.end() );
}

std::string
Node::ToString()
{
	std::stringstream ret;
	ret << "Node ID: " << data.nodeID << " has " << edges.size() << " edges " << std::endl;
	
	for ( auto &edge : edges ) 
	{
		Node* tempNode = edge.End();
		ret << "Node ID: " << data.nodeID << " is connected to Node: " << tempNode->data.nodeID << " cost: " << edge.Data().cost << std::endl;
	}

	return ret.str();
}

void Node::MarkAsTraversed(bool traversed_)
{
	data.traversed = traversed_;

}