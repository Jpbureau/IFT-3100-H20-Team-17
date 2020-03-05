#pragma once

#include "ofxGui.h"
#include "textureDrawer.h" //Pour faire fonctionner les string
#include "textureDrawer3D.h"

class CameraGui
{
public:
	CameraGui();
	void setup(int positionX, int positionY);
	void update();
	void draw();
private:
	ofxPanel CameraPanel;

	ofParameter<float> xCoordinateSlider;
	ofParameter<float> yCoordinateSlider;
	ofParameter<float> zCoordinateSlider;

	ofParameter<float> xRotationSlider; //pan
	ofParameter<float> yRotationSlider; //tilt
	ofParameter<float> zRotationSlider; //roll 

	ofParameter<float> horizontalAngleSlider;
	ofParameter<float> verticalAngleSlider;

	ofParameter<float> frustumCloseSlider;
	ofParameter<float> frustumFarSlider;

	ofParameter<string> selectedViewMode;
	ofxButton perpesctiveModeButton;

	ofxButton resetCameraButton;

	bool perspective;

	void resetCamera();
	void changerPerspective();
};