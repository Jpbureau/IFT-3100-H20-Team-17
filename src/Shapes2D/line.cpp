#include "line.h"

Line::Line(glm::vec2 p1, glm::vec2 p2, float lineWidth, ofColor color, string name):
	p1(p1), p2(p2), lineWidth(lineWidth), color(color), selected(name, false)
{
	representation->setup(selected);
}

void Line::draw()
{
	ofNoFill();
	ofSetLineWidth(lineWidth);
	ofSetColor(color);
	ofDrawLine(p1, p2);

	if (selected) drawSelectionRectangle();
}

void Line::update()
{
}

bool Line::isPointInside(int x, int y)
{
	int x1 = p1.x;
	int y1 = p1.y;
	int x2 = p2.x;
	int y2 = p2.y;

	//on doit inverser les coordonnées si le clique est plus grand que le release afin d'uniformiser la comparaison plus bas		
	if (x2 < x1) {
		int temp = x2;
		x2 = x1;
		x1 = temp;
	}

	if (y2 < y1) {
		int temp = y2;
		y2 = y1;
		y1 = temp;
	}

	return x > x1 && x < x2 && y > y1 && y < y2;
}

void Line::select()
{
	selected = true;
}

void Line::unselect()
{
	selected = false;
}

bool Line::isSelected()
{
	return selected;
}

ofxBaseGui * Line::getGuiRepresentation()
{
	return representation.get();
}

void Line::drawSelectionRectangle()
{
	ofNoFill();
	ofSetLineWidth(2);
	ofSetColor(11, 252, 3);
	ofDrawRectangle(p1.x, p1.y, (p2 - p1).x, (p2 - p1).y);
}
