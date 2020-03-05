#pragma once

#include "ofxGui.h"
#include "textureDrawer3D.h"
#include "fileManagerGui.h"
#include "ofxAssimpModelLoader.h"

class Canvas3DGui
{
public:
	Canvas3DGui(TextureDrawer3D& drawer, FileManager& manager);

	void setup();
	void update();
	void draw();

private:
	ofxPanel optionsPanel;
	ofxButton boiteDelimButton;
	ofxButton importModelButton;

	TextureDrawer3D& textureDrawer3D;
	FileManager& fileManager;

	ofParameter<ofColor> modelColorPicker;

	void boiteDelimButtonClicked();
	void importModelClicked();
};
