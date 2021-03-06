//#include "Graph.h"
//#include "Node.h"
//#include <vector>
//#include <map>
//#include <algorithm>
//
//struct PF_Node
//{	
//	Node* node;
//	Node* parent;
//	int g, h;
//	int F() const { return g + h; }
//	bool operator < (const PF_Node& pfNode_){ return this->F() < pfNode_.F(); }
//	bool operator == (PF_Node pfNode_) { return this->node == pfNode_.node; }
//	PF_Node(Node* node_) : node(node_), parent(nullptr), g(2000000000), h(0){}
//	PF_Node(Node* node_, int g_) : node(node_), parent(nullptr), g(g_), h(0){}
//	PF_Node(Node* node_, int g_, int h_) : node(node_), parent(nullptr), g(g_), h(h_){}
//	PF_Node() : node(nullptr), parent(nullptr), g(0), h(0){}
//};
//
//struct PF_NodeQueue
//{
//	std::vector<PF_Node> queue;
//	void Sort() { std::sort(queue.begin(), queue.end()); }
//	PF_Node RemoveFirstElem() 
//	{ 
//		PF_Node ret = queue[0]; 
//		queue.erase(queue.begin());
//		return ret;
//	}
//	PF_Node RemoveLastElem()
//	{
//		PF_Node ret = queue[queue.size()-1];
//		queue.erase(queue.end()-1);
//		return ret;
//	}
//	void PushBack(const PF_Node& node_){ queue.push_back(node_); }
//	PF_Node& Find(Node* node_)
//	{ 
//		PF_Node node(node_);
//		return *(std::find(queue.begin(), queue.end(), node)); 	
//	}
//	PF_Node& Find(PF_Node node_)
//	{
//		return *(std::find(queue.begin(), queue.end(), node_));
//	}
//	PF_Node& operator[] (Node* node_)
//	{
//		PF_Node node(node_);
//		return *(std::find(queue.begin(), queue.end(), node));
//	}
//	bool Contains(const PF_Node& node_)
//	{ 
//		if (std::find(queue.begin(), queue.end(), node_) == queue.end())
//			return false;
//		return true;
//	}
//	PF_Node& Parent(const PF_Node& node_)
//	{
//		return Find(node_.parent);
//	}
//
//	std::vector<Node*> Path(PF_Node& end_)
//	{
//		PF_Node currentNode = end_;
//		std::vector<Node*> ret;
//		
//		while (currentNode.parent != nullptr)
//		{
//			ret.push_back(currentNode.node);
//			currentNode = Parent(currentNode);
//		} 
//
//		return ret;
//	}
//	bool Empty() { return queue.empty(); }
//
//	int Size()
//	{
//		return queue.size();
//	}
//};
//

//
//#pragma once
//class PathFinder
//{
//public:
//	PathFinder();
//	~PathFinder();
//
//	std::vector<Node*> Dijkstras(const Graph& graph_, NodeRenderData& renderData_, int speedMillis_ = 250);
//	std::vector<Node*> AStar(const Graph& graph_, NodeRenderData& renderData_, int speedMillis_ = 250);
//	std::vector<Node*> BFS(const Graph& graph_, NodeRenderData& renderData_, int speedMillis_ = 250);
//	std::vector<Node*> DFS(const Graph& graph_, NodeRenderData& renderData_, int speedMillis_ = 250);
//
//private:
//
//
//
//	
//
//};
//
