#include "imagePrimitive.h"

ImagePrimitive::ImagePrimitive(ofImage image, glm::vec2 p1, glm::vec2 p2, string name) :
	image(image), p1(p1), p2(p2), selected(name, false)
{
	representation->setup(selected);
}

void ImagePrimitive::draw()
{
	ofFill();
	ofSetColor(255);
	image.draw(p1, p2.x - p1.x, p2.y - p1.y);

	if (selected) drawSelectionRectangle();
}

void ImagePrimitive::update()
{
}

bool ImagePrimitive::isPointInside(int x, int y)
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

void ImagePrimitive::select()
{
	selected = true;
}

void ImagePrimitive::unselect()
{
	selected = false;
}

bool ImagePrimitive::isSelected()
{
	return selected;
}

ofxBaseGui* ImagePrimitive::getGuiRepresentation()
{
	return representation.get();
}

void ImagePrimitive::drawSelectionRectangle()
{
	ofNoFill();
	ofSetLineWidth(2);
	ofSetColor(11, 252, 3);
	ofDrawRectangle(p1.x, p1.y, (p2 - p1).x, (p2 - p1).y);
}
