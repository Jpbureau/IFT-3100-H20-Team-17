#pragma once

#include "ofxGui.h"
#include "textureDrawer3D.h"

class PrimitivesGeometriquesGui
{
public:
	PrimitivesGeometriquesGui(TextureDrawer3D& drawer);

	void setup(int positionX, int positionY);
	void update();
	void draw();
private:
	TextureDrawer3D& textureDrawer3D;

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
	ofxButton drawIcosahedronType;
	ofxButton drawSphereType;
	
	ofxButton drawEllipseType;
	ofxButton drawPolygonType;
	ofxButton drawCylinderType;
	ofxButton drawRectangleType;
	ofxButton drawConeType;

	ofParameter<GLfloat> platonSolidRadiusSlider;
	ofParameter<GLfloat> heightSlider;
	ofParameter<GLfloat> widthSlider;
	ofParameter<GLfloat> depthSlider;

	ofParameter<GLfloat> xCoordinateSlider;
	ofParameter<GLfloat> yCoordinateSlider;
	ofParameter<GLfloat> zCoordinateSlider;

	ofParameter<int> nbSidesSlider;

	void selectTetrahedronType();
	void selectHexahedronType();
	void selectOctahedronType();
	void selectDodecahedronType();
	void selectIcosahedronType();
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

