#pragma once

class GraphPrimitive {
public:
	virtual void update() = 0;
	virtual void draw() = 0;

	virtual bool isPointInside(int x, int y) = 0;

	virtual void select() = 0;
	virtual void unselect() = 0;
	virtual bool isSelected() = 0;
};