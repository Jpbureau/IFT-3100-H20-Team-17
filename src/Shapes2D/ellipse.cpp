#include "ellipse.h"

Ellipse2D::Ellipse2D(glm::vec2 p1, glm::vec2 p2, float strokeWidth, ofColor fillColor, ofColor strokeColor):
	p1(p1), p2(p2), strokeWidth(strokeWidth), fillColor(fillColor), strokeColor(strokeColor)
{
}

void Ellipse2D::draw()
{
	glm::vec2 center = p1 + (p2 - p1) / 2;

	float diameter_x = p2.x - p1.x;
	float diameter_y = p2.y - p1.y;

	ofFill();
	ofSetLineWidth(strokeWidth);
	ofSetCircleResolution(48);
	ofSetColor(fillColor);
	ofDrawEllipse(center, diameter_x, diameter_y);

	ofNoFill();
	ofSetColor(strokeColor);
	ofDrawEllipse(center, diameter_x, diameter_y);
}

void Ellipse2D::update()
{
}

bool Ellipse2D::isPointInside(int x, int y)
{
	return false;
}

void Ellipse2D::select()
{
}

void Ellipse2D::unselect()
{
}
