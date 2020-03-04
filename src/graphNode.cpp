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

bool GraphNode::isPointInside(int x, int y)
{
	for (auto& child : children) {
		if (child->isPointInside(x, y)) {
			return true;
		}
	}
	return false;
}

void GraphNode::select()
{
	for (auto& child : children) {
		child->select();
	}
}

void GraphNode::unselect()
{
	for (auto& child : children) {
		child->unselect();
	}
}

void GraphNode::addChild(GraphPrimitive* child)
{
	children.push_back(std::unique_ptr<GraphPrimitive>(child));
}

void GraphNode::selectChildsAtPoint(int x, int y)
{
	bool isAnyShapeSelected = false;

	for (auto& child : children) {
		if (child->isPointInside(x, y)) {
			child->select();
			isAnyShapeSelected = true;
		}
	}

	if (!isAnyShapeSelected) {
		unselect();
	}
}
