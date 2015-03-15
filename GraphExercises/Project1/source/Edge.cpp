#include "Edge.h"

Edge::Edge(Node* end_, EdgeData data_)
{
	end = end_;
	data = data_;
}

Edge::~Edge(void)
{
}

Node*
Edge::End()
{
	return end;
}

EdgeData
Edge::Data()
{
	return data;
}

void Edge::SetCost(int cost_)
{
	data.cost = cost_;
}