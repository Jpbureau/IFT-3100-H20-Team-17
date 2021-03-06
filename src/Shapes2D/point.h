#pragma once

#include "ofMain.h"
#include "graphPrimitive.h"

class Point : public GraphPrimitive {
public:
	Point(glm::vec2 position, float radius, ofColor color, string name);

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
	glm::vec2 position;
	float radius;
	ofColor color;

	ofParameter<bool> selected;
	void drawSelectionRectangle();

	std::unique_ptr<ofxToggle> representation = std::make_unique<ofxToggle>();
};