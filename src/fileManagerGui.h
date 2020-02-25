#pragma once

#include "ofxGui.h"
#include "fileManager.h"

class FileManagerGui {
public:
	void setup();
	void draw();

private:
	FileManager fileManager;

	ofxPanel menuPanel;

	ofxButton importButton;
	void importButton_pressed();

	ofxButton exportButton;
	void exportButtonPressed();
};