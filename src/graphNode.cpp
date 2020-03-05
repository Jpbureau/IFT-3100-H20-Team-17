#include "graphNode.h"

GraphNode::GraphNode()
{
}

GraphNode::GraphNode(std::list<std::shared_ptr<GraphPrimitive>> children):
	children(children)
{
}

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

bool GraphNode::isSelected()
{
	bool selected = true;

	for (auto& child : children) {
		selected = selected && child->isSelected();
	}
	
	return selected;
}

void GraphNode::addChild(GraphPrimitive* child)
{
	children.push_back(std::shared_ptr<GraphPrimitive>(child));
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

void GraphNode::deleteSelectedPrimitives()
{
	children.remove_if([](std::shared_ptr<GraphPrimitive>& child) { return child->isSelected(); });
}

void GraphNode::createGroupWithSelectedPrimitives()
{
	std::list<std::shared_ptr<GraphPrimitive>> selectedPrimitives;

	for (auto child : children) {
		if (child->isSelected()) {
			selectedPrimitives.push_back(child);
		}
	}

	children.remove_if([](std::shared_ptr<GraphPrimitive>& child) { return child->isSelected(); });

	addChild(new GraphNode(selectedPrimitives));
}
