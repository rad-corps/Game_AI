#pragma once

#include <vector>
#include "Node.h"
#include "SpriteBatch.h"
#include "Texture.h"

class Renderer
{
public:
	void Draw(std::vector<Node*> nodes_, unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_ = 255);
	void Draw(Node* node_, unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_ = 255);

	Renderer(SpriteBatch* spriteBatch_);
	~Renderer();

private: 
	Texture* nodeSprite;
	SpriteBatch* spriteBatch;
};

struct NodeRenderData
{
	std::vector<Node*> openList;
	std::vector<Node*> closedList;
	Node* currentNode;	

	NodeRenderData() : currentNode(nullptr) {}

	void Clear()
	{
		openList.clear();
		closedList.clear();
		currentNode = nullptr;
	}
};