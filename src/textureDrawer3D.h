#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include <vector>


enum class ShaderType { none, lambert };

enum class ModelType { model, box, cylinder, cone, sphere };


class TextureDrawer3D
{
public:
	void setup(int canvasPositionX, int canvasPositionY, int canvasSize);
	void draw();
	void update();
	void importModel(string modelPath);

	void updateModelParameters(ofColor color, float modelScale);
	void updateAnimationParameters(float rotationSpeed, float waveIntensity, bool rotationAnimation, bool waveAnimation);
	void updateShaderSelection(ShaderType selected);

	bool isMouseInsideModelCanvas(int x, int y);

	void selectSphereType();
	void selectCylinderType();
	void selectBoxType();
	void selectConeType();
	void selectModelType();


private:
	int modelCanvasSize;
	int modelCanvasX;
	int modelCanvasY;
	int centerX;
	int centerY;

	float modelScale = 0.3f;

	bool useRotationAnimation;
	bool useLevitationAnimation;
	float waveIntensity;
	float rotationSpeed;

	ofFbo fboTexture3D;

	void drawBoiteDelimitation();

	void applyLambertShader();
	ShaderType selectedShader;

	ofxAssimpModelLoader model;
	ofSpherePrimitive sphere;
	ofBoxPrimitive box;
	ofConePrimitive cone;
	ofCylinderPrimitive cylinder;

	ofMesh mesh;
	ofShader shader;
	ofLight light;
	ofColor modelColor;
	ofEasyCam cam;
	ofMaterial material;

	ModelType selectedType;

	ofPoint pointSupGaucheBoite;
	int largeurModel3D;
	int hauteurModel3D;
	int profondeurModel3D;

	float stroke_width;
	float radius;

	void drawModel();
	void resetCamera();
};
