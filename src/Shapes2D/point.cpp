#include "point.h"

Point::Point(glm::vec2 position, float radius, ofColor color) :
	position(position), radius(radius), color(color)
{
}

void Point::draw()
{
	ofFill();
	ofSetLineWidth(1.0f);
	ofSetColor(color);
	ofDrawEllipse(position.x, position.y, radius, radius);
}

void Point::update()
{
}

bool Point::isPointInside(int x, int y)
{
	return false;
}

void Point::select()
{
}

void Point::unselect()
{
}
