#pragma once

#include "ofMain.h"
#include "graphPrimitive.h"

class Point : public GraphPrimitive {
public:
	Point(glm::vec2 position, float radius, ofColor color);

	virtual void draw();
	virtual void update();

private:
	glm::vec2 position;
	float radius;
	ofColor color;
};