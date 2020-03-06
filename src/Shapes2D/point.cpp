#include "point.h"

Point::Point(glm::vec2 position, float radius, ofColor color, string name) :
	position(position), radius(radius), color(color), selected(name, false)
{
	representation->setup(selected);
}

void Point::draw()
{
	ofFill();
	ofSetLineWidth(1.0f);
	ofSetColor(color);
	ofDrawEllipse(position.x, position.y, radius, radius);

	if (selected) drawSelectionRectangle();
}

void Point::update()
{
}

void Point::updateCommonAttributes(ofColor fill, ofColor stroke, float strokeWidth)
{
	this->color = stroke;
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
	selected = true;
}

void Point::unselect()
{
	selected = false;
}

bool Point::isSelected()
{
	return selected;
}

ofxBaseGui * Point::getGuiRepresentation()
{
	return representation.get();
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
