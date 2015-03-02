#include "Graph.h"
#include <sstream>
#include <algorithm>

using namespace std;

int DirectedGraph::nodeID = 0;

DirectedGraph::DirectedGraph(void)
{
	nodeSprite = new Texture("./Images/nodeTexture.png");
	startNode = nullptr;
	endNode = nullptr;
	
}

DirectedGraph::~DirectedGraph(void)
{
	delete nodeSprite;
}

void DirectedGraph::DFS_Step()
{
	//is this the first time we have been called? i.e. has the start node been traversed?
	if (!startNode->GetData().traversed)
	{
		searchStack.push_back(startNode);
	}


	if (searchStack.empty())
	{
		return;
	}
	//while (!searchStack.empty())
	//{
		//get the top off the stack 
		currentNode = searchStack[searchStack.size()-1];
		searchStack.erase(searchStack.end() - 1);

		//process it : ??


		//mark as traversed
		currentNode->MarkAsTraversed(); 

		//for all of the edges that this node has, add to the stack
		for (auto& edge : currentNode->GetEdges())
		{
			Node* edgeDestNode = edge.End();
			
			//if this edgeDestNode has not been traversed
			if (!edgeDestNode->GetData().traversed)
			{
				//if this edgeDestNode is not already on the stack
				if (std::find(searchStack.begin(), searchStack.end(), edgeDestNode) == searchStack.end())
				{
					//add it to the stack
					searchStack.push_back(edgeDestNode);
				}
			}

		}
	//}

}

void
DirectedGraph::Draw(SpriteBatch* spriteBatch_)
{
	//draw the links first
	for (int i = 0; i < size(); ++i)
	{
		Node* node = graphData[i];
		//get the edge
		for (Edge edge : node->GetEdges())
		{
			//draw line from this node to edge
			Node* startNode = node;
			Node* endNode = edge.End();

			if ( startNode != endNode )
				spriteBatch_->DrawArrow(startNode->GetData().pos.x, startNode->GetData().pos.y, endNode->GetData().pos.x, endNode->GetData().pos.y);
		}
	}

	//then draw the nodes
	for (int i = 0; i < size(); ++i)
	{
		Node* node = graphData[i];
		NodeData data = node->GetData();
		if (data.traversed)
			spriteBatch_->SetRenderColor(0, 255, 255, 255);
		else if (!data.traversed)
			spriteBatch_->SetRenderColor(50, 50, 255, 255);
		if (node == startNode)
			spriteBatch_->SetRenderColor(50, 255, 50, 255);
		if (node == endNode)
			spriteBatch_->SetRenderColor(255, 50, 50, 255);
		if ( node == currentNode)
			spriteBatch_->SetRenderColor(255, 255, 255, 255);
		
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
	nd.traversed = false;
	//nd.start = false;
	//nd.end = false;

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
	vector<Node*> nodeVec = FindNodes(pos_, tollerance_);
	for (auto& node : nodeVec )
	{
		RemoveNode(node);
	}
}

void DirectedGraph::SetStartNode(Vector2 pos_, int tollerance_)
{
	startNode = FindNode(pos_, tollerance_);
}

void DirectedGraph::SetEndNode(Vector2 pos_, int tollerance_)
{
	endNode = FindNode(pos_, tollerance_);
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

std::vector<Node*> DirectedGraph::FindNodes(Vector2 pos_, int tollerance_)
{
	vector<Node*> ret;
	
	for (auto &node : graphData)
	{
		float distance = (node->GetData().pos - pos_).GetMagnitude();

		if (distance < tollerance_)
		{
			ret.push_back(node);
		}
	}

	return ret;
}


void DirectedGraph::ConnectCloseNodes(Node* nodeA_, int distance_)
{
	vector<Node*> nodeVec = FindNodes(nodeA_->GetData().pos, distance_);
	for ( auto& node : nodeVec )
	{		
		ConnectNodes(node, nodeA_, 1);
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