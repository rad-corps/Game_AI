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

std::vector<Node*> PathFinder::Dijkstras(const Graph& graph_, NodeRenderData& renderData_)
{
	//add all nodes in graph to a PF_NodeQueue
	PF_NodeQueue masterList;
	PF_NodeQueue openList;
	PF_NodeQueue closedList;
	PF_Node currentNode;

	for (Node* node : graph_.GraphData())
	{
		//calc the heuristic
		int h = 0;

		if (graph_.StartNode() == node)
		{
			masterList.PushBack(PF_Node(node, 0, h));
			openList.PushBack(PF_Node(node, 0, h));
			renderData_.openList.push_back(node);
		}
		else
		{
			masterList.PushBack(PF_Node(node, 999999, h));
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

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
		
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	return masterList.Path(currentNode);
}