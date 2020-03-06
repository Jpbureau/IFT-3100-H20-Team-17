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

	ofxGuiGroup animationOptions;
	ofxGuiGroup shaderType;

	TextureDrawer3D& textureDrawer3D;
	FileManager& fileManager;

	ofParameter<ofColor> modelColorPicker;

	ofParameter<float> rotationSpeed;
	ofParameter<float> waveIntensity;
	ofParameter<bool> rotationAnimationToggle;
	ofParameter<bool> levitationAnimationToggle;

	ofxButton lambertShaderSelectedButton;
	ofxButton noShaderSelectedButton;

	void boiteDelimButtonClicked();
	void importModelClicked();

	void lambertShaderSelected();
	void noShaderSelected();
};
