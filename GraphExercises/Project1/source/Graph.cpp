#include "Graph.h"
#include <sstream>
#include <algorithm>

int DirectedGraph::nodeID = 0;

DirectedGraph::DirectedGraph(void)
{
}

DirectedGraph::~DirectedGraph(void)
{
}

Node*
DirectedGraph::AddNode(NodeData data_)
{
	Node *nodePtr = new Node(data_);
	graphData.push_back(nodePtr);
	return nodePtr;
}

Node*
DirectedGraph::AddNode(Vector2 pos_)
{
	NodeData nd;
	nd.pos = pos_;
	nd.nodeID = nodeID++;

	Node *nodePtr = new Node(nd);
	graphData.push_back(nodePtr);
	return nodePtr;
}

void DirectedGraph::RemoveNode(Node* node_)
{
	//remove any edges associated with this node
	for ( auto &node : graphData )
	{
		node->RemoveEdgeIf(node_);
	}

	//remove the node itself from graphdata
	auto it = std::find(graphData.begin(), graphData.end(), node_);
	if ( it != graphData.end() )
	{
		delete node_;
		graphData.erase(it);
	}
}

Node* DirectedGraph::operator[](int index_)
{
	return graphData[index_];
}

int
DirectedGraph::size()
{
	return graphData.size();
}

std::string DirectedGraph::ToString()
{
	std::stringstream str;
	for ( auto &node : graphData ) 
	{
		str << node->ToString();
	}
	return str.str();
}

void DirectedGraph::ConnectNodes(Node* nodeA_, Node* nodeB_, EdgeData edgeData_)
{
	nodeA_->AddEdge(nodeB_, edgeData_);
}

void DirectedGraph::ConnectNodes(Node* nodeA_, Node* nodeB_, int cost_)
{
	EdgeData ed;
	ed.cost = cost_;
	nodeA_->AddEdge(nodeB_, ed);
}