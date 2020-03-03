#pragma once

#include "ofMain.h"
#include "graphPrimitive.h"

class Ellipse2D : public GraphPrimitive {
public:
	Ellipse2D(glm::vec2 p1, glm::vec2 p2, float strokeWidth, ofColor fillColor, ofColor strokeColor);

	virtual void draw();
	virtual void update();

private:
	glm::vec2 p1;
	glm::vec2 p2;
	float strokeWidth;
	ofColor fillColor;
	ofColor strokeColor;
};