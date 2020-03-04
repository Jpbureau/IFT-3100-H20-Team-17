#pragma once

#include "ofMain.h"
#include "graphPrimitive.h"

class Line : public GraphPrimitive {
public:
	Line(glm::vec2 p1, glm::vec2 p2, float lineWidth, ofColor color);

	virtual void draw();
	virtual void update();

	virtual bool isPointInside(int x, int y);

	virtual void select();
	virtual void unselect();
	virtual bool isSelected();

private:
	glm::vec2 p1;
	glm::vec2 p2;
	float lineWidth;
	ofColor color;

	bool selected;
	void drawSelectionRectangle();
};