#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "fileManager.h"

class Renderer
{
private:
	FileManager fileManager;

	ofxPanel gui;
	ofxButton exportButton;
	void exportButtonPressed();

public:
	Renderer(const FileManager& fileManager);

	void setup();
	void draw();
};