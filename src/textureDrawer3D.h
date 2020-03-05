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
	void updateAnimationParameters(float rotationSpeed, float waveIntensity, bool rotationAnimation, bool waveAnimation);

private:
	const int drawingCanvasSize = 600;
	int drawingCanvasX = 1500;
	int drawingCanvasY =500;
	int centerX = drawingCanvasX + drawingCanvasSize / 2;
	int centerY = drawingCanvasY + drawingCanvasSize / 2;

	float modelScale = 0.3f;

	bool useRotationAnimation;
	bool useLevitationAnimation;
	float waveIntensity;
	float rotationSpeed;

	ofFbo fboTexture3D;

	void calculerBoiteDelimitation();
	void drawBoiteDelimitation(ofPoint point, float width, float height, float depth);

	ofxAssimpModelLoader model;
	ofMesh mesh;
	ofShader shader;
	ofLight light;
	ofColor modelColor;
	ofEasyCam cam;

	ofPoint pointSupGaucheBoite;
	int largeurModel3D;
	int hauteurModel3D;
	int profondeurModel3D;
};
