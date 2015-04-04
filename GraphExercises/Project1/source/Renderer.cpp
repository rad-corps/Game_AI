#include "Renderer.h"


Renderer::Renderer(SpriteBatch* spriteBatch_) 
: spriteBatch(spriteBatch_)
{
	nodeSprite = new Texture("./Images/nodeTexture.png");
}


Renderer::~Renderer()
{
}

void Renderer::Draw(std::vector<Node*> nodes_, unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_)
{
	spriteBatch->SetRenderColor(r_, g_, b_, a_);
	
	for (auto &node : nodes_)
	{
		spriteBatch->DrawSprite(nodeSprite, node->pos.x, node->pos.y);
	}	
}

void Renderer::Draw(Node* node_, unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_)
{
	if (node_ != nullptr)
	{
		spriteBatch->SetRenderColor(r_, g_, b_, a_);
		spriteBatch->DrawSprite(nodeSprite, node_->pos.x, node_->pos.y);
	}
}