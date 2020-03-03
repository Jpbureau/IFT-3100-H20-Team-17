#pragma once

#include <memory>
#include <list>

#include "graphPrimitive.h"

class GraphNode: public GraphPrimitive {
public:
	virtual void update();
	virtual void draw();

	void addChild(GraphPrimitive* child);

protected:
	std::list<std::unique_ptr<GraphPrimitive>> children;
};