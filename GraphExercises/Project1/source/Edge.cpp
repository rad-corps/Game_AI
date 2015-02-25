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