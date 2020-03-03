#include "line.h"

Line::Line(glm::vec2 p1, glm::vec2 p2, float lineWidth, ofColor color):
	p1(p1), p2(p2), lineWidth(lineWidth), color(color)
{
}

void Line::draw()
{
	ofNoFill();
	ofSetLineWidth(lineWidth);
	ofSetColor(color);
	ofDrawLine(p1, p2);
}

void Line::update()
{
}
