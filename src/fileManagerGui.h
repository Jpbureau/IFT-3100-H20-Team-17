#pragma once

#include "ofxGui.h"
#include "fileManager.h"
#include "textureDrawer.h"

class FileManagerGui {
public:
	FileManagerGui(FileManager& manager, TextureDrawer& textureDrawer);

	void setup();
	void draw();

private:
	FileManager& fileManager;
	TextureDrawer& textureDrawer;

	ofxPanel menuPanel;

	ofxButton importButton;
	void importButton_pressed();

	ofxButton exportButton;
	void exportButtonPressed();
};