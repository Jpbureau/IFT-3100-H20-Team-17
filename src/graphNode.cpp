#include "graphNode.h"

GraphNode::GraphNode(std::string name)
{
	representation->setup(name);
}

GraphNode::GraphNode(std::list<std::shared_ptr<GraphPrimitive>> children, std::string name):
	children(children)
{
	representation->setup(name);
	updateRepresentation();
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

void GraphNode::updateCommonAttributes(ofColor fill, ofColor stroke, float strokeWidth)
{
	for (auto child : children) {
		if (child->isSelected()) {
			child->updateCommonAttributes(fill, stroke, strokeWidth);
		}
	}
}

void GraphNode::translate(int x, int y)
{
	for (auto& child : children) {
		if (child->isSelected()) {
			child->translate(x, y);
		}
	}
}

void GraphNode::scale(glm::vec2 s)
{
	for (auto& child : children) {
		if (child->isSelected()) {
			child->scale(s);
		}
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

ofxBaseGui* GraphNode::getGuiRepresentation()
{
	return representation.get();
}

void GraphNode::addChild(GraphPrimitive* child)
{
	children.push_back(std::shared_ptr<GraphPrimitive>(child));
	representation->add((child->getGuiRepresentation()));
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
	updateRepresentation();
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

	addChild(new GraphNode(selectedPrimitives, "Group"));
	
	updateRepresentation();
}

void GraphNode::ungroupSelected()
{
	std::list<std::shared_ptr<GraphNode>> selectedNodes;

	for (auto child : children) {
		std::shared_ptr<GraphNode> node = std::dynamic_pointer_cast<GraphNode>(child);

		if (node != nullptr && node->isSelected()) {
			selectedNodes.push_back(node);
		}
	}

	children.remove_if([](std::shared_ptr<GraphPrimitive>& child) {
		return std::dynamic_pointer_cast<GraphNode>(child) != nullptr && child->isSelected();
	});

	for (auto node : selectedNodes) {
		for (auto child : node->children) {
			children.push_back(child);
		}
	}

	updateRepresentation();
}



void GraphNode::updateRepresentation()
{
	representation->clear();
	
	for (auto& child : children) {
		representation->add(child->getGuiRepresentation());
	}
}