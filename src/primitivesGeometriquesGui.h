#pragma once

#include "ofxGui.h"
#include "textureDrawer.h"

class PrimitivesGeometriquesGui
{
public:
	PrimitivesGeometriquesGui();

	void setup(int positionX, int positionY);
	void update();
	void draw();
private:
	ofxPanel primitivesGeometriquesPanel;

	ofxGuiGroup optionsGeneral;
	ofxGuiGroup optionsPlatonSolid;
	ofxGuiGroup optionsOtherShapes;
	ofxGuiGroup optionsAction;

	ofParameter<string> selectedType;

	ofParameter<ofColor> strokeColorPicker;
	ofParameter<ofColor> fillColorPicker;
	
	ofxButton placeObjectButton;
	ofxButton selectButton;
	ofxButton deselectButton;
	ofxButton deleteButton;

	ofxButton drawTetrahedronType;
	ofxButton drawHexahedronType;
	ofxButton drawOctahedronType;
	ofxButton drawDodecahedronType;
	ofxButton drawIsocahedronType;
	ofxButton drawSphereType;
	
	ofxButton drawEllipseType;
	ofxButton drawPolygonType;
	ofxButton drawCylinderType;
	ofxButton drawRectangleType;
	ofxButton drawConeType;

	ofParameter<float> platonSolidRadiusSlider;
	ofParameter<float> otherShapesRadiusSlider;
	ofParameter<float> heightSlider;
	ofParameter<float> widthSlider;
	ofParameter<float> depthSlider;

	ofParameter<float> xCoordinateSlider;
	ofParameter<float> yCoordinateSlider;
	ofParameter<float> zCoordinateSlider;

	ofParameter<int> nbSidesSlider;

	void selectTetrahedronType();
	void selectHexahedronType();
	void selectOctahedronType();
	void selectDodecahedronType();
	void selectIsocahedronType();
	void selectSphereType();

	void selectEllipseType();
	void selectPolygonType();
	void selectCylinderType();
	void selectRectangleType();
	void selectConeType();

	void placeObjectAction();
	void selectAction();
	void deleteAction();
	void deselectAction();
};

