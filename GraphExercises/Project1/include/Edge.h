#pragma once

struct Node;

struct Edge
{
	Edge(Node* end_, int cost_);
	~Edge(void);

	int cost;
	Node* end;
};

