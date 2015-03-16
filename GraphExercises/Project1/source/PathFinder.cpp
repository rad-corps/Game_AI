#include "PathFinder.h"
#include <limits>
#include <algorithm>


PathFinder::PathFinder()
{
}


PathFinder::~PathFinder()
{
}

std::vector<Node*> PathFinder::Dijkstras(Graph& graph_)
{
	std::vector<Node*> path; //the function return value
	Node* startNode_ = graph_.StartNode();
	Node* endNode_ = graph_.EndNode();
	NodePathFinderData startNode;
	NodePathFinderData endNode;
	std::vector<NodePathFinderData> openList;
	std::vector<NodePathFinderData> closedList;
	std::vector<NodePathFinderData> pathFinderData;
	NodePathFinderData currentNode;
	Node* currentRawNode;

	//add all nodes to pathfinder data
	for (Node* node : graph_.GraphData())
	{
		NodePathFinderData data;
		data.parent = nullptr;
		data.node = node;
		
		if (startNode_ != node)
		{
			data.gScore = INT_MAX;
		}
		else
		{
			data.gScore = 0;
			openList.push_back(data);
			startNode = data;
		}

		if (endNode_ == node)
		{
			endNode = data;
		}

		pathFinderData.push_back(data);
	}

	while (!openList.empty())
	{
		std::sort(openList.begin(), openList.end());
		currentNode = openList[0];
		if (currentNode.node == endNode_)
			break;
		
		openList.erase(openList.begin());
		closedList.push_back(currentNode);

		for (Edge& edge : currentNode.node->GetEdges())
		{
			NodePathFinderData tempData;
			tempData.node = edge.End();
			//	Add c.connection to openList if not in closedList
			if (std::find(closedList.begin(), closedList.end(), tempData) == closedList.end())
			{
				//find it in pathFinderData
				auto it = std::find(pathFinderData.begin(), pathFinderData.end(), tempData);
				
				openList.push_back(*it);
		
				if (currentNode.gScore > edge.Data().cost + it->gScore)
				{
					//	c.connection.gScore = currentNode.gScore + c.cost
					it->gScore = currentNode.gScore + edge.Data().cost;
		
					//	c.connection.parent = currentNode
					it->parent = currentNode.node;
				}
			}
		}
	}

	currentRawNode = currentNode.node;
	while (currentRawNode != nullptr)
	{
		//	Add currentNode.position to path
		path.push_back(currentRawNode);
	
		//	currentNode = currentNode.parent
		currentRawNode = currentNode.parent;

		NodePathFinderData tempData;
		tempData.node = currentNode.parent;
		auto it = std::find(pathFinderData.begin(), pathFinderData.end(), tempData);
		if (it == pathFinderData.end())
		{
			currentRawNode = nullptr;
		}
		else
		{
			currentNode = (*it);
		}
	}

	return path;
}