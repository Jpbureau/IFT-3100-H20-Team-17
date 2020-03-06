#pragma once

#include <memory>
#include <list>

#include "graphPrimitive.h"

class GraphNode: public GraphPrimitive {
public:
	GraphNode(std::string name);
	GraphNode(std::list<std::shared_ptr<GraphPrimitive>> children, std::string name);

	virtual void update();
	virtual void draw();

	virtual bool isPointInside(int x, int y);

	virtual void select();
	virtual void unselect();
	virtual bool isSelected();

	virtual ofxBaseGui* getGuiRepresentation();

	void addChild(GraphPrimitive* child);
	void selectChildsAtPoint(int x, int y);
	void deleteSelectedPrimitives();
	void createGroupWithSelectedPrimitives();
	void ungroupSelected();

protected:
	std::list<std::shared_ptr<GraphPrimitive>> children;

private:
	std::unique_ptr<ofxGuiGroup> representation = std::make_unique<ofxGuiGroup>();

	void updateRepresentation();
};