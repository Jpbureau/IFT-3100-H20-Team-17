#pragma once

#include "ofMain.h"
#include "graphPrimitive.h"

class Point : public GraphPrimitive {
public:
	Point(glm::vec2 position, float radius, ofColor color);

	virtual void draw();
	virtual void update();

	virtual bool isPointInside(int x, int y);

	virtual void select();
	virtual void unselect();

private:
	glm::vec2 position;
	float radius;
	ofColor color;

	bool isSelected;
	void drawSelectionRectangle();
};