#include "Graph.h"
#include <sstream>
#include <algorithm>


int DirectedGraph::nodeID = 0;

DirectedGraph::DirectedGraph(void)
{
	nodeSprite = new Texture("./Images/nodeTexture.png");
}

DirectedGraph::~DirectedGraph(void)
{
	delete nodeSprite;
}

void
DirectedGraph::Draw(SpriteBatch* spriteBatch_)
{
	//get the nodes
	for (int i = 0; i < size(); ++i)
	{
		Node* node = graphData[i];
		//get the edge
		for (Edge edge : node->GetEdges())
		{
			//draw line from this node to edge
			Node* startNode = node;
			Node* endNode = edge.End();

			spriteBatch_->DrawLine(startNode->GetData().pos.x, startNode->GetData().pos.y, endNode->GetData().pos.x, endNode->GetData().pos.y);
		}
	}

	for (int i = 0; i < size(); ++i)
	{
		Node* node = graphData[i];
		NodeData data = node->GetData();
		spriteBatch_->DrawSprite(nodeSprite, data.pos.x, data.pos.y);
	}
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

void DirectedGraph::RemoveNodeIf(Vector2 pos_, int tollerance_)
{
	Node* node = FindNode(pos_, tollerance_);
	if (node != nullptr)
	{
		RemoveNode(node);
	}
}

Node* DirectedGraph::FindNode(Vector2 pos_, int tollerance_)
{
	for (auto &node : graphData)
	{
		float distance = (node->GetData().pos - pos_).GetMagnitude();

		if (distance < tollerance_)
		{			
			return node;
		}
	}
}

void DirectedGraph::ConnectCloseNodes(Node* nodeA_, int distance_)
{
	Node* nodeB = FindNode(nodeA_->GetData().pos, distance_);
	if (nodeB != nullptr)
	{
		ConnectNodes(nodeA_, nodeB, 1);
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