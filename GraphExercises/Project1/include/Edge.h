#pragma once

class Node;

struct EdgeData
{
	int cost;
};


class Edge
{
public:
	Edge(Node* end_, EdgeData data_);
	~Edge(void);
	Node* End();

private:
	//Node* start;
	Node* end;
	EdgeData data;
};

