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
	FileManager fileManager;

	ofxPanel gui;
	ofxButton exportButton;
	void exportButtonPressed();
};