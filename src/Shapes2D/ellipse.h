#pragma once

#include "ofMain.h"
#include "graphPrimitive.h"

class Ellipse2D : public GraphPrimitive {
public:
	Ellipse2D(glm::vec2 p1, glm::vec2 p2, float strokeWidth, ofColor fillColor, ofColor strokeColor, string name);

	virtual void draw();
	virtual void update();

	virtual void updateCommonAttributes(ofColor fill, ofColor stroke, float strokeWidth);
	virtual void translate(int x, int y);
	virtual void scale(glm::vec2 s);

	virtual bool isPointInside(int x, int y);

	virtual void select();
	virtual void unselect();
	virtual bool isSelected();

	virtual ofxBaseGui* getGuiRepresentation();

private:
	glm::vec2 p1;
	glm::vec2 p2;
	float strokeWidth;
	ofColor fillColor;
	ofColor strokeColor;

	ofParameter<bool> selected;
	void drawSelectionRectangle();

	std::unique_ptr<ofxToggle> representation = std::make_unique<ofxToggle>();
};