#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include <vector>

enum class ShaderType { none, lambert };

class TextureDrawer3D
{
public:
	void setup(int canvasPositionX, int canvasPositionY, int canvasSize);
	void draw();
	void update();
	void importModel(ofxAssimpModelLoader& model);

	void updateModelParameters(ofColor color, float modelScale);
	void updateAnimationParameters(float rotationSpeed, float waveIntensity, bool rotationAnimation, bool waveAnimation);
	void updateShaderSelection(ShaderType selected);

	bool isMouseInsideModelCanvas(int x, int y);

private:
	int modelCanvasSize = 800;
	int modelCanvasX = 850;
	int modelCanvasY = 100;
	int centerX;
	int centerY;

	float modelScale = 0.3f;

	bool useRotationAnimation;
	bool useLevitationAnimation;
	float waveIntensity;
	float rotationSpeed;

	ofFbo fboTexture3D;

	void calculerBoiteDelimitation();
	void drawBoiteDelimitation(ofPoint point, float width, float height, float depth);

	void applyLambertShader();
	ShaderType selectedShader;

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
