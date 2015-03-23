#include "PathFinder.h"
#include <limits>
#include <algorithm>
#include <chrono>
#include <thread>
#include <iostream>


PathFinder::PathFinder()
{
}


PathFinder::~PathFinder()
{
}

std::vector<Node*> PathFinder::Dijkstras2(const Graph& graph_)
{
	//add all nodes in graph to a PF_NodeQueue
	PF_NodeQueue masterList;
	PF_NodeQueue openList;
	PF_NodeQueue closedList;
	PF_Node currentNode;

	for (Node* node : graph_.GraphData())
	{
		if (graph_.StartNode() == node)
		{
			masterList.PushBack(PF_Node(node, 0));
			openList.PushBack(PF_Node(node, 0));
		}
		else
		{
			masterList.PushBack(PF_Node(node));
		}
	}

	while (!openList.Empty())
	{
		openList.Sort();
		currentNode = openList.RemoveFirstElem();
		if (currentNode.node == graph_.EndNode())
			break;

		closedList.PushBack(currentNode);

		for (Edge& edge : currentNode.node->GetEdges())
		{
			//PF_Node edgeEnd = masterList.Find(edge.End());
			//	Add c.connection to openList if not in closedList
			if (!closedList.Contains(masterList[edge.End()]))
			{			
				if (masterList[edge.End()].F() > currentNode.F() + edge.Data().cost)
				{
					//	c.connection.gScore = currentNode.gScore + c.cost
					masterList[edge.End()].g = currentNode.g + edge.Data().cost;

					//	c.connection.parent = currentNode
					masterList[edge.End()].parent = currentNode.node;
				}

				openList.PushBack(masterList[edge.End()]);
			}
		}
	}

	return masterList.Path(currentNode);
}

std::vector<Node*> PathFinder::AStar(const Graph& graph_, NodeRenderData& renderData_)
{
	//add all nodes in graph to a PF_NodeQueue
	PF_NodeQueue masterList;
	PF_NodeQueue openList;
	PF_NodeQueue closedList;
	PF_Node currentNode;

	for (Node* node : graph_.GraphData())
	{
		//calc the heuristic
		int h = (int)(node->GetData().pos - graph_.EndNode()->GetData().pos).GetMagnitude();

		if (graph_.StartNode() == node)
		{
			masterList.PushBack(PF_Node(node, 0, h));
			openList.PushBack(PF_Node(node, 0, h));
			renderData_.openList.push_back(node);
		}
		else
		{
			masterList.PushBack(PF_Node(node, 999999,h));
		}
	}

	while (!openList.Empty())
	{
		auto start_time = std::chrono::high_resolution_clock::now();

		openList.Sort();
		currentNode = openList.RemoveFirstElem();
		renderData_.currentNode = currentNode.node;
		if (currentNode.node == graph_.EndNode())
			break;

		closedList.PushBack(currentNode);
		renderData_.closedList.push_back(currentNode.node);

		for (Edge& edge : currentNode.node->GetEdges())
		{
			//PF_Node edgeEnd = masterList.Find(edge.End());
			//	Add c.connection to openList if not in closedList
			if (!closedList.Contains(masterList[edge.End()]))
			{
				if (masterList[edge.End()].F() > currentNode.F() + edge.Data().cost)
				{
					//	c.connection.gScore = currentNode.gScore + c.cost
					masterList[edge.End()].g = currentNode.g + edge.Data().cost;

					//	c.connection.parent = currentNode
					masterList[edge.End()].parent = currentNode.node;
				}

				if (!openList.Contains(masterList[edge.End()]))
				{
					openList.PushBack(masterList[edge.End()]);
					renderData_.openList.push_back(edge.End());
				}				
			}
		}
		auto end_time = std::chrono::high_resolution_clock::now();
		auto time = end_time - start_time;
		std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() << endl;
		std::cout << "openList size: " << openList.Size() << endl;
		std::cout << "closedList size: " << closedList.Size() << endl;
		
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

	return masterList.Path(currentNode);
}


std::vector<Node*> PathFinder::Dijkstras(const Graph& graph_)
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
			//data.gScore = INT_MAX;
			data.gScore = 2000000000; //less than INT_MAX so we dont cause overflow. 
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
		
				if (it->gScore > currentNode.gScore + edge.Data().cost)
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