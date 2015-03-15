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

	void SetCost(int cost_);

	Node* End();
	EdgeData Data();

private:

	Node* end;
	EdgeData data;
};

