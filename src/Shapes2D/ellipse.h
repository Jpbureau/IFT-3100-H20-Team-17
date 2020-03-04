#pragma once

#include "ofMain.h"
#include "graphPrimitive.h"

class Ellipse2D : public GraphPrimitive {
public:
	Ellipse2D(glm::vec2 p1, glm::vec2 p2, float strokeWidth, ofColor fillColor, ofColor strokeColor);

	virtual void draw();
	virtual void update();

	virtual bool isPointInside(int x, int y);

	virtual void select();
	virtual void unselect();

private:
	glm::vec2 p1;
	glm::vec2 p2;
	float strokeWidth;
	ofColor fillColor;
	ofColor strokeColor;
};