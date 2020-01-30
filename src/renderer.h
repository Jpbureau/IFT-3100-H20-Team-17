#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "fileManager.h"

class Renderer
{
public:
	Renderer(const FileManager & fileManager);

	void setup();
	void draw();

private:
	const FileManager& fileManager;

	ofxPanel gui;
	ofxButton exportButton;
	void exportButtonPressed();
};