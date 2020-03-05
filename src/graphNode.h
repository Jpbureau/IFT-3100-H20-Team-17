#pragma once

#include <memory>
#include <list>
#include <algorithm>

#include "graphPrimitive.h"

class GraphNode: public GraphPrimitive {
public:
	GraphNode();
	GraphNode(std::list<std::shared_ptr<GraphPrimitive>> children);

	virtual void update();
	virtual void draw();

	virtual bool isPointInside(int x, int y);

	virtual void select();
	virtual void unselect();
	virtual bool isSelected();

	void addChild(GraphPrimitive* child);
	void selectChildsAtPoint(int x, int y);
	void deleteSelectedPrimitives();
	void createGroupWithSelectedPrimitives();

protected:
	std::list<std::shared_ptr<GraphPrimitive>> children;
};