#include "point.h"

Point::Point(glm::vec2 position, float radius, ofColor color) :
	position(position), radius(radius), color(color), isSelected(false)
{
}

void Point::draw()
{
	ofFill();
	ofSetLineWidth(1.0f);
	ofSetColor(color);
	ofDrawEllipse(position.x, position.y, radius, radius);

	if (isSelected) {
		drawSelectionRectangle();
	}
}

void Point::update()
{
}

bool Point::isPointInside(int x, int y)
{
	return (
		position.x - radius < x &&
		x < position.x + radius &&
		position.y - radius < y &&
		y < position.y + radius 
	);
}

void Point::select()
{
	isSelected = true;
}

void Point::unselect()
{
	isSelected = false;
}

void Point::drawSelectionRectangle()
{
	ofNoFill();
	ofSetLineWidth(2);
	ofSetColor(11, 252, 3);
	int x = position.x - radius / 2;
	int y = position.y - radius / 2;
	ofDrawRectangle(x, y, radius, radius);
}
