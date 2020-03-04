#include "rectangle.h"

Rectangle2D::Rectangle2D(glm::vec2 p1, glm::vec2 p2, float strokeWidth, ofColor fillColor, ofColor strokeColor):
	p1(p1), p2(p2), strokeWidth(strokeWidth), fillColor(fillColor), strokeColor(strokeColor)
{
}

void Rectangle2D::draw()
{
	ofFill();
	ofSetLineWidth(strokeWidth);
	ofSetColor(fillColor);
	ofDrawRectangle(p1, p2.x - p1.x, p2.y - p1.y);
	ofNoFill();
	ofSetColor(strokeColor);
	ofDrawRectangle(p1, p2.x - p1.x, p2.y - p1.y);
}

void Rectangle2D::update()
{
}

bool Rectangle2D::isPointInside(int x, int y)
{
	return false;
}

void Rectangle2D::select()
{
}

void Rectangle2D::unselect()
{
}
