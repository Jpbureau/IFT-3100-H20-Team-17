#include "ellipse.h"

Ellipse2D::Ellipse2D(glm::vec2 p1, glm::vec2 p2, float strokeWidth, ofColor fillColor, ofColor strokeColor, string name):
	p1(p1), p2(p2), strokeWidth(strokeWidth), fillColor(fillColor), strokeColor(strokeColor), selected(name, false)
{
	representation->setup(selected);
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

	if (selected) drawSelectionRectangle();
}

void Ellipse2D::update()
{
}

void Ellipse2D::updateCommonAttributes(ofColor fill, ofColor stroke, float strokeWidth)
{
	this->fillColor = fill;
	this->strokeColor = stroke;
	this->strokeWidth = strokeWidth;
}

void Ellipse2D::translate(int x, int y)
{
	glm::vec2 t(x, y);
	p1 += t;
	p2 += t;
}

void Ellipse2D::scale(glm::vec2 s)
{
	glm::vec2 prop = s / (p2 - p1);
	glm::vec2 center = p1 + (p2 - p1) / 2;
	p1 *= prop;
	p2 *= prop;
	glm::vec2 center2 = p1 + (p2 - p1) / 2;
	glm::vec2 offset = (center - center2);
	translate(offset.x, offset.y);
}

bool Ellipse2D::isPointInside(int x, int y)
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

void Ellipse2D::select()
{
	selected = true;
}

void Ellipse2D::unselect()
{
	selected = false;
}

bool Ellipse2D::isSelected()
{
	return selected;
}

ofxBaseGui * Ellipse2D::getGuiRepresentation()
{
	return representation.get();
}

void Ellipse2D::drawSelectionRectangle()
{
	ofNoFill();
	ofSetLineWidth(2);
	ofSetColor(11, 252, 3);
	ofDrawRectangle(p1.x, p1.y, (p2 - p1).x, (p2 - p1).y);
}
