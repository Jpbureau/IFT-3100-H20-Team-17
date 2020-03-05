#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include <vector>

class TextureDrawer3D
{
public:
	void setup();
	void draw();
	void update();
	void importModel(ofxAssimpModelLoader& model);

	void updateColors(ofColor color);

private:
	const int drawingCanvasSize = 600;
	int drawingCanvasX = 235 + drawingCanvasSize;
	int drawingCanvasY = ofGetHeight() / 3.5;
	int centerX = drawingCanvasX + drawingCanvasSize / 2;
	int centerY = drawingCanvasY + drawingCanvasSize / 2;

	float modelScale = 1.5f;

	bool use_rotation = false;

	ofFbo fboTexture3D;

	void calculerBoiteDelimitation();
	void drawBoiteDelimitation(ofPoint point, float width, float height, float depth);

	ofxAssimpModelLoader model;
	ofMesh mesh;
	ofShader shader;
	ofLight light;
	ofColor modelColor;

	ofPoint pointSupGaucheBoite;
	int largeurModel3D;
	int hauteurModel3D;
	int profondeurModel3D;
};
