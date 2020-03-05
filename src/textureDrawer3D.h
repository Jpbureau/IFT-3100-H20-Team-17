#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include "cam.h"
#include <vector>

class TextureDrawer3D
{
public:
	void setup();
	void draw();
	void update();
	void resetCamera();

private:
	const int drawingCanvasSize = 600;
	int drawingCanvasX = 225;
	int drawingCanvasY = ofGetHeight() / 3.5;

	Cam camera;

	ofFbo fboTexture3D;

	void calculerBoiteDelimitation();
	void drawBoiteDelimitation(ofPoint point, float width, float height, float depth);

	ofxAssimpModelLoader teapot;
	ofMesh mesh;

	ofPoint pointSupGaucheBoite;
	int largeurModel3D;
	int hauteurModel3D;
	int profondeurModel3D;
};
