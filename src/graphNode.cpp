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

void GraphNode::addChild(GraphPrimitive* child)
{
	children.push_back(std::unique_ptr<GraphPrimitive>(child));
}
