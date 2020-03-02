#pragma once

#include <memory>
#include <list>

class GraphNode {
public:
	virtual void update();
	virtual void draw();

	void addChild(std::unique_ptr<GraphNode> child);

protected:
	std::list<std::unique_ptr<GraphNode>> children;
};