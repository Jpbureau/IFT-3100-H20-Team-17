#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "fileManager.h"
#include "cursor.h"
#include "textureDrawer.h"

class Renderer
{
public:
	void setup();
	void update();
	void draw();

	const int drawingCanvasSize = 600;
	int drawingCanvasX = 225;
	int drawingCanvasY = ofGetHeight() / 3.5;

	ofFbo fboTexture;

	int mousePosX;
	int mousePosY;
	Cursor cursor;
	TextureDrawer textureDrawer;

	void mousePressed(int x, int y);
	void mouseReleased(int x, int y);

private:
	ofImage image;

	ofParameter<ofColor> backGroundColor;
	ofParameter<ofColor> strokeColorPicker;
	ofParameter<ofColor> fillColorPicker;
	ofParameter<float> strokeWeightSlider;
	ofParameter<float> radiusSlider;

	FileManager fileManager;

	ofxPanel menuPanel;
	ofxPanel drawingOptionsPanel;
	ofxGuiGroup optionsPoint;

	ofxButton drawLineButton;
	ofxButton drawPointButton;
	ofxButton drawRectangleButton;
	ofxButton drawSquareButton;
	ofxButton drawEllipseButton;
	ofxButton drawCircleButton;
	ofxButton selectButton;
	ofxButton deselectButton;
	ofxButton deleteButton;

	ofxButton importButton;
	void importButton_pressed();

	ofxButton exportButton;
	void exportButtonPressed();

	void selectPointType();
	void selectLineType();
	void selectRectangleType();
	void selectSquareType();
	void selectEllipseType();
	void selectCircleType();
	void selectAction();
	void deleteAction();
	void deselectAction();
};