#pragma once

#include "ofxGui.h"

class Canvas3DGui
{
public:
	Canvas3DGui();

	void setup();
	void update();
	void draw();

private:
	ofxPanel optionsPanel;
	ofxButton boiteDelimButton;

	void boiteDelimButtonClicked();

};

