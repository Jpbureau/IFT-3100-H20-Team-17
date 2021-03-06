#pragma once

#include "ofxGui.h"
#include "textureDrawer.h"

class CanvasGui {
public:
	CanvasGui(TextureDrawer& drawer);

	void setup(int drawingCanvasY);
	void update();
	void draw();

	ofParameter<ofColor> backGroundColor;

private:
	TextureDrawer& textureDrawer;

	ofParameter<ofColor> strokeColorPicker;
	ofParameter<ofColor> fillColorPicker;
	ofParameter<float> strokeWeightSlider;
	ofParameter<float> radiusSlider;
	ofParameter<string> selectedType;

	ofxButton applyToSelectedButton;
	void applyToSelectedAction();

	ofxPanel drawingOptionsPanel;
	ofxGuiGroup optionsPoint;
	ofxGuiGroup shapeSelectionGroup;

	ofxButton drawLineButton;
	ofxButton drawPointButton;
	ofxButton drawRectangleButton;
	ofxButton drawSquareButton;
	ofxButton drawEllipseButton;
	ofxButton drawCircleButton;
	ofxButton selectButton;
	ofxButton deselectButton;
	ofxButton translateButton;
	ofxButton scaleButton;
	ofxButton deleteButton;
	ofxButton groupButton;
	ofxButton ungroupButton;

	void selectPointType();
	void selectLineType();
	void selectRectangleType();
	void selectSquareType();
	void selectEllipseType();
	void selectCircleType();
	void selectAction();
	void deselectAction();
	void translateAction();
	void scaleAction();
	void deleteAction();
	void groupAction();
	void ungroupAction();
};