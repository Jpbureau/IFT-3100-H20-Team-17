#pragma once

#include "ofxGui.h"
#include "textureDrawer3D.h"
#include "fileManagerGui.h"
#include "ofxAssimpModelLoader.h"

class Canvas3DGui
{
public:
	Canvas3DGui(TextureDrawer3D& drawer, FileManager& manager);

	void setup(int canvasPositionX, int canvasPositionY, int canvasSize);
	void update();
	void draw();

private:
	ofxPanel optionsPanel;
	ofParameter<bool> boiteDelimitationToggle;
	ofxButton importModelButton;

	ofxButton selectModelTypeButton;
	ofxButton selectBoxTypeButton;
	ofxButton selectSphereTypeButton;
	ofxButton selectCylinderTypeButton;
	ofxButton selectConeTypeButton;

	ofxGuiGroup animationOptions;
	ofxGuiGroup shaderType;
	ofxGuiGroup selectionType;

	TextureDrawer3D& textureDrawer3D;
	FileManager& fileManager;

	ofParameter<ofColor> modelColorPicker;
	ofParameter<float> modelScale;

	ofParameter<string> selectedShaderType;
	ofParameter<string> selectedPrimitiveType;

	ofParameter<float> rotationSpeed;
	ofParameter<float> waveIntensity;
	ofParameter<bool> rotationAnimationToggle;
	ofParameter<bool> levitationAnimationToggle;

	ofxButton lambertShaderSelectedButton;
	ofxButton noShaderSelectedButton;
	ofxButton noiseShaderSelectedButton;

	//void boiteDelimButtonClicked();
	void importModelClicked();

	void lambertShaderSelected();
	void noiseShaderSelected();
	void noShaderSelected();

	void selectModelType();
	void selectBoxType();
	void selectSphereType();
	void selectCylinderType();
	void selectConeType();
};
