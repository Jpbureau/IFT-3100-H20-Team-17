#pragma once

#include "ofxGui.h"
#include "fileManager.h"
#include "textureDrawer.h"
#include "recorder.h"

class FileManagerGui {
public:
	FileManagerGui(FileManager& manager, TextureDrawer& textureDrawer, Recorder& recorder);

	void setup();
	void draw();

private:
	FileManager& fileManager;
	TextureDrawer& textureDrawer;
	Recorder& recorder;

	ofxPanel menuPanel;

	ofxButton importButton;
	void importButton_pressed();

	ofxButton exportButton;
	void exportButtonPressed();
};