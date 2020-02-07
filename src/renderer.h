#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "fileManager.h"

class Renderer
{
public:
	void setup();
	void draw();

private:
	ofImage image;

	FileManager fileManager;

	ofxPanel gui;

	ofxButton importButton;
	void importButton_pressed();

	ofxButton exportButton;
	void exportButtonPressed();
};