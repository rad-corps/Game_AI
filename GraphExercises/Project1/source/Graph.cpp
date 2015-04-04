#include "Graph.h"
#include <sstream>
#include <algorithm>

using namespace std;

int Graph::nodeID = 0;

Graph::Graph(void)
{
	nodeSprite = new Texture("./Images/nodeTexture.png");
	startNode = nullptr;
	endNode = nullptr;
	costFont = new Font("./Fonts/CourierNew_11px.fnt");
}

Graph::~Graph(void)
{
	delete nodeSprite;
}

void Graph::Clear()
{
	graphData.clear();
	ClearStartAndEndNodes();
}


void Graph::ClearStartAndEndNodes()
{
	startNode = nullptr;
	endNode = nullptr;
}

void
Graph::SetHilightedNodes(vector<Node*> highlitedNodes_)
{
	highlitedNodes = highlitedNodes_;
}

Node* Graph::StartNode() const
{
	return startNode;
}

Node* Graph::EndNode() const 
{
	return endNode;
}

std::vector<Node*> 
Graph::GraphData(void) const 
{
	return graphData;
}

//void Graph::BFS_Step()
//{
//	//is this the first time we have been called? i.e. has the start node been traversed?
//	if (!startNode->GetData().traversed)
//		searchStack.push_back(startNode);
//	
//	if (searchStack.empty() || currentNode == endNode)
//		return;
//
//	//get the top off the stack 	
//	currentNode = searchStack[0];
//	searchStack.erase(searchStack.begin());	
//
//	//process it : ??
//
//	//mark as traversed
//	currentNode->MarkAsTraversed();
//
//	//for all of the edges that this node has, add to the stack
//	for (auto& edge : currentNode->GetEdges())
//	{
//		Node* edgeDestNode = edge.End();
//
//		//if this edgeDestNode has not been traversed
//		if (!edgeDestNode->GetData().traversed)
//		{
//			//if this edgeDestNode is not already on the stack
//			if (std::find(searchStack.begin(), searchStack.end(), edgeDestNode) == searchStack.end())
//			{
//				//add it to the stack
//				searchStack.push_back(edgeDestNode);
//			}
//		}
//
//	}
//}
//
void Graph::PrepareForSearch()
{
	searchStack.clear();
	openList.clear();
	closedList.clear();
	path.clear();
	highlitedNodes.clear();
	
	//set all gScores to 0 ?
	for (Node* node : graphData)
	{
		node->g = 0;
		node->f = 0;
	}

	currentNode = nullptr;
}
//
//std::vector<Node*> Graph::FindPathDijkstras()
//{
//
//	//set startNode to 0 and all other gScores to infinity
//	for (Node* node : graphData)
//	{
//		if (node != startNode)
//			node->SetGScore(INT_MAX);
//		else
//			node->SetGScore(0);
//	}
//
//	openList.push_back(startNode);
//
//	//	While openList is not empty
//	while (!openList.empty())
//	{
//		//	Sort openList by Node.gScore
//		std::sort(openList.begin(), openList.end());
//
//		//	Let currentNode = first item in openList
//		currentNode = openList[0];
//
//		//	// Process the node, do what you want with it. EG:
//		//if currentNode is one of the potentialEnd
//		if (currentNode == endNode)
//		{
//			//	endNode = currentNode
//			//	break out of loop
//			break;
//		}
//
//		//	remove currentNode from openList
//		openList.erase(openList.begin());
//
//		//	Add currentNode to closedList
//		closedList.push_back(currentNode);
//
//		//for all connections c in currentNode
//		for (Edge& edge : currentNode->GetEdges())
//		{
//			//	Add c.connection to openList if not in closedList
//			if (std::find(closedList.begin(), closedList.end(), edge.End()) == closedList.end())
//			{
//				openList.push_back(edge.End());
//
//				if (currentNode->GetData().gScore + edge.Data().cost < edge.End()->GetData().gScore)
//				{
//					//	c.connection.gScore = currentNode.gScore + c.cost
//					edge.End()->SetGScore(currentNode->GetData().gScore + edge.Data().cost);
//
//					//	c.connection.parent = currentNode
//					edge.End()->SetParent(currentNode);
//				}				
//			}
//		}
//	}
//
//	//While currentNode != NULL
//	while (currentNode != nullptr)
//	{
//		//	Add currentNode.position to path
//		path.push_back(currentNode);
//
//		//	currentNode = currentNode.parent
//		currentNode = currentNode->GetParent();
//	}
//		
//	return path;
//}
//
//void Graph::Dijkstra_Step()
//{
//
//
//}
//
//void Graph::DFS_Step()
//{	
//	//is this the first time we have been called? i.e. has the start node been traversed?
//	if (!startNode->GetData().traversed)
//		searchStack.push_back(startNode);
//	
//	if (searchStack.empty() || currentNode == endNode)	
//		return;
//
//	//get the top off the stack 	
//	currentNode = searchStack[searchStack.size()-1];
//	searchStack.pop_back();
//	//searchStack.erase(searchStack.end() - 1);
//
//	//process it : ??
//
//	//mark as traversed
//	currentNode->MarkAsTraversed(); 
//
//	//for all of the edges that this node has, add to the stack
//	for (auto& edge : currentNode->GetEdges())
//	{
//		Node* edgeDestNode = edge.End();
//			
//		//if this edgeDestNode has not been traversed
//		if (!edgeDestNode->GetData().traversed)
//		{
//			//if this edgeDestNode is not already on the stack
//			if (std::find(searchStack.begin(), searchStack.end(), edgeDestNode) == searchStack.end())
//			{
//				//add it to the stack
//				searchStack.push_back(edgeDestNode);
//			}
//		}
//
//	}
//}

void
Graph::Draw(SpriteBatch* spriteBatch_, Font *font_)
{
	//draw the links first
	for (int i = 0; i < size(); ++i)
	{
		Node* node = graphData[i];
		//get the edge
		for (Edge edge : node->edges)
		{
			
			Node* startNode = node;
			Node* endNode = edge.end;

			//draw line from this node to edge
			if ( startNode != endNode )
				spriteBatch_->DrawArrow(startNode->pos.x, startNode->pos.y, endNode->pos.x, endNode->pos.y);

			//also draw the cost/distance 
			stringstream costString;
			costString << edge.cost;

			//find a spot to draw it (halfway between start and end nodes)
			Vector2 strPos = (startNode->pos + endNode->pos) * 0.5;
			spriteBatch_->DrawString(costFont, costString.str().c_str(), strPos.x, strPos.y);
		}
	}

	////then draw the nodes
	//for (int i = 0; i < size(); ++i)
	//{
	//	Node* node = graphData[i];
	//	NodeData data = node->GetData();
	//	if (data.traversed)
	//		spriteBatch_->SetRenderColor(0, 255, 255, 255);
	//	else if (!data.traversed)
	//		spriteBatch_->SetRenderColor(50, 50, 255, 255);
	//	if (node == startNode)
	//		spriteBatch_->SetRenderColor(50, 255, 50, 255);
	//	if (node == endNode)
	//		spriteBatch_->SetRenderColor(255, 50, 50, 255);
	//	if ( node == currentNode)
	//		spriteBatch_->SetRenderColor(255, 255, 255, 255);
	//	if (std::find(highlitedNodes.begin(), highlitedNodes.end(), node) != highlitedNodes.end())
	//		spriteBatch_->SetRenderColor(0, 255, 0, 255);

	//	
	//	spriteBatch_->DrawSprite(nodeSprite, data.pos.x, data.pos.y);
	//}
}
//
//Node*
//Graph::AddNode(NodeData data_)
//{
//	Node *nodePtr = new Node(data_);
//	graphData.push_back(nodePtr);
//	return nodePtr;
//}

Node*
Graph::AddNode(Vector2 pos_)
{
	Node *nodePtr = new Node();
	nodePtr->pos = pos_;
	graphData.push_back(nodePtr);
	return nodePtr;
}

void Graph::RemoveNode(Node* node_)
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

void Graph::RemoveNodeIf(Vector2 pos_, int tollerance_)
{
	vector<Node*> nodeVec = FindNodes(pos_, tollerance_);
	for (auto& node : nodeVec )
	{
		RemoveNode(node);
	}
}

bool Graph::NodeWithin(Vector2 pos_, int tollerance_)
{
	if (FindNode(pos_, tollerance_) == nullptr)
		return false;
	return true;
}

void Graph::SetStartNode(Vector2 pos_, int tollerance_)
{
	startNode = FindNode(pos_, tollerance_);
}

void Graph::SetEndNode(Vector2 pos_, int tollerance_)
{
	endNode = FindNode(pos_, tollerance_);
}

Node* Graph::FindNode(Vector2 pos_, int tollerance_)
{
	for (auto &node : graphData)
	{
		float distance = (node->pos - pos_).GetMagnitude();

		if (distance < tollerance_)
		{			
			return node;
		}
	}
	return nullptr;
}

std::vector<Node*> Graph::FindNodes(Vector2 pos_, int tollerance_)
{
	vector<Node*> ret;
	
	for (auto &node : graphData)
	{
		float distance = (node->pos - pos_).GetMagnitude();

		if (distance < tollerance_)
		{
			ret.push_back(node);
		}
	}

	return ret;
}

Node* Graph::operator[](int index_)
{
	return graphData[index_];
}

int
Graph::size()
{
	return graphData.size();
}

std::string Graph::ToString()
{
	std::stringstream str;
	for ( auto &node : graphData ) 
	{
		str << node->ToString();
	}
	return str.str();
}

void Graph::ConnectCloseNodes(Node* nodeA_, int distance_, bool bidirectional_)
{
	vector<Node*> nodeVec = FindNodes(nodeA_->pos, distance_);
	for (auto& node : nodeVec)
	{
		if (node != nodeA_)
		{
			int distance = (int)(node->pos - nodeA_->pos).GetMagnitude();
			ConnectNodes(node, nodeA_, distance, bidirectional_);
		}
	}
}

void Graph::ConnectNodes(Node* nodeA_, Node* nodeB_, int cost_, bool bidirectional_)
{
	nodeA_->AddEdge(nodeB_, cost_);
	
	if (bidirectional_)
		nodeB_->AddEdge(nodeA_, cost_);
}


std::vector<Node*> Graph::ReconstructPath()
{}


//TOFIX make this a function pointer for different heuristics? 
int Graph::CalcH(Node* from_, Node* to_)
{
	//straight line distance
	return (int)(to_->pos - from_->pos).GetMagnitude();
}

std::vector<Node*> Graph::AStar()
{
	//closedset: = the empty set    // The set of nodes already evaluated.
	std::vector<Node*> closedList;

	//openset : = { start }    // The set of tentative nodes to be evaluated, initially containing the start node
	std::vector<Node*> openList;
	openList.push_back(startNode);

	//set all g scores to infinite and all parents to nullptr
	for (Node* node : graphData)
	{
		node->g = 9999999;
		node->parent = nullptr;
	}

	//	g_score[start] : = 0    // Cost from start along best known path.
	openList[0]->g = 0;
	//openList[0]->parent = openList[0];

//	// Estimated total cost from start to goal through y.
//	f_score[start] : = g_score[start] + heuristic_cost_estimate(start, goal)
	openList[0]->f = openList[0]->g + CalcH(openList[0], endNode);

//	while openset is not empty
	while (!openList.empty())
	{
		//lowest f score node to go to front
		std::sort(openList.begin(), openList.end());
		
		//get the lowest f score node TODO: are we getting the lowest or highest here? test
		Node* currentNode = openList[openList.size() - 1];

		//remove the node from the open list
		openList.erase(openList.begin() + openList.size() - 1);

		//add it to the closed (traversed list) 
		closedList.push_back(currentNode);

		//if we have found the end node. 
		if (currentNode == endNode)
		{
			//success: bail from loop and create the return list
			break;
		}

		//loop through edges
		for (Edge& edge : currentNode->edges)
		{
			//if end node is not traversed (does not appear in closed list) 
			if (std::find(closedList.begin(), closedList.end(), edge.end) == closedList.end())
			{
				//calculate a tentative f cost of the edge's end node
				int tentativeF = currentNode->g + edge.cost + CalcH(edge.end, endNode);
				
				//if the tentative f cost is less than the edge node's current f cost, update its data
				if (tentativeF < edge.end->f)
				{
					edge.end->parent = currentNode;
					edge.end->g = currentNode->g + edge.cost;
					edge.end->f = tentativeF;
					if (std::find(openList.begin(), openList.end(), edge.end) == openList.end())
					{
						openList.push_back(edge.end);
					}
				}
			}
		}
	}//while(!openList.empty())

	//reconstruct the path
	std::vector<Node*> ret; 
	Node* currentNode = endNode;
	do
	{
		ret.push_back(currentNode);
		currentNode = currentNode->parent;
	} while (currentNode != nullptr);

	return ret;

}