#include "graphNode.h"

void GraphNode::update()
{
	for (auto& child : children) {
		child->update();
	}
}

void GraphNode::draw()
{
	for (auto& child : children) {
		child->draw();
	}
}

void GraphNode::addChild(std::unique_ptr<GraphNode> child)
{
	children.push_back(child);
}
