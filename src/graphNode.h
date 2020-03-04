#pragma once

#include <memory>
#include <list>

#include "graphPrimitive.h"

class GraphNode: public GraphPrimitive {
public:
	virtual void update();
	virtual void draw();

	virtual bool isPointInside(int x, int y);

	virtual void select();
	virtual void unselect();

	void addChild(GraphPrimitive* child);
	void selectChildsAtPoint(int x, int y);

protected:
	std::list<std::unique_ptr<GraphPrimitive>> children;
};