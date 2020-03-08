#include "textureDrawer3D.h"

void TextureDrawer3D::setup(int canvasPositionX, int canvasPositionY, int canvasSize)
{
	this->modelCanvasX = canvasPositionX;
	this->modelCanvasY = canvasPositionY;
	this->modelCanvasSize = canvasSize;
	this->centerX = modelCanvasX + modelCanvasSize / 2;
	this->centerY = modelCanvasY + modelCanvasSize / 2;

	model.loadModel("teapot.obj");

	selectedShader = ShaderType::none;
	selectedType = ModelType::model;

	mesh = model.getMesh(0);
	model.setPosition(centerX, centerY, 90);
	shader.load("lambert_330_vs.glsl", "lambert_330_fs.glsl");

	cam.setControlArea(ofRectangle(modelCanvasX, modelCanvasY, modelCanvasSize, modelCanvasSize));
	cam.setTarget(glm::vec3(centerX, centerY, 90));
	cam.setupPerspective(true, 60, 0, 0, glm::vec2( -0.4 , -0.1));
	cam.setDistance(700);

	sphere.setScale(modelScale * 20);
	sphere.setPosition(glm::vec3(centerX, centerY, 90));
	sphere.setRadius(30.0);

	cylinder.setScale(modelScale * 10);
	cylinder.setPosition(glm::vec3(centerX, centerY, 90));

	box.setScale(modelScale * 10);
	box.setPosition(glm::vec3(centerX, centerY, 90));

	cone.setScale(modelScale * 20);
	cone.setPosition(glm::vec3(centerX, centerY, 90));
}

void TextureDrawer3D::update()
{
	model.setScale(modelScale, modelScale, modelScale);
	sphere.setScale(modelScale * 20);
	cylinder.setScale(modelScale * 8);
	box.setScale(modelScale * 8);
	cone.setScale(modelScale * 17);

	if (useRotationAnimation) {
		model.setRotation(0, ofGetFrameNum() * rotationSpeed, 0.0f, 1.0f, 0.0f);
		box.rotateDeg(rotationSpeed, glm::vec3(0, 1, 0));
		cone.rotateDeg(rotationSpeed, glm::vec3(0, 1, 0));
		sphere.rotateDeg(rotationSpeed, glm::vec3(0, 1, 0));
		cylinder.rotateDeg(rotationSpeed, glm::vec3(0, 1, 0));
	}

	if (useLevitationAnimation) {
		model.setPosition(centerX, centerY + 30 * sin(ofGetFrameNum() / waveIntensity), 90);
		box.setPosition(centerX, centerY + 30 * sin(ofGetFrameNum() / waveIntensity), 90);
		sphere.setPosition(centerX, centerY + 30 * sin(ofGetFrameNum() / waveIntensity), 90);
		cone.setPosition(centerX, centerY + 30 * sin(ofGetFrameNum() / waveIntensity), 90);
		cylinder.setPosition(centerX, centerY + 30 * sin(ofGetFrameNum() / waveIntensity), 90);
	}

	switch (selectedShader)
	{
	case ShaderType::none:
		model.enableMaterials();
		break;
	case ShaderType::lambert:
		applyLambertShader();
		break;
	case ShaderType::noise:
		applyNoiseShader();
		break;
	default:
		break;
	}

}

void TextureDrawer3D::importModel(string modelPath)
{
	model.loadModel(modelPath);
	model.setPosition(centerX, centerY, 90);
	resetCamera();
}

void TextureDrawer3D::updateModelParameters(ofColor color, float modelScale)
{
	this->modelColor = color;
	this->modelScale = modelScale;
}

void TextureDrawer3D::updateAnimationParameters(float rotationSpeed, float waveIntensity, bool rotationAnimation, bool waveAnimation)
{
	this->rotationSpeed = rotationSpeed;
	this->waveIntensity= waveIntensity;
	this->useRotationAnimation = rotationAnimation;
	this->useLevitationAnimation = waveAnimation;
}

void TextureDrawer3D::updateDelimitationBox(bool boiteDelimitation)
{
	this->boiteDelimitation = boiteDelimitation;
}

void TextureDrawer3D::updateShaderSelection(ShaderType selected)
{
	switch (selected)
	{
	case ShaderType::lambert:
		selectedShader = selected;
		shader.unload();
		shader.load("lambert_330_vs.glsl", "lambert_330_fs.glsl");
		break;
	case ShaderType::noise:
		selectedShader = selected;
		shader.unload();
		shader.load("shaders_gl3/noise.vert", "shaders_gl3/noise.frag");
		break;
	case ShaderType::none:
		selectedShader = selected;
		light = ofLight();
		break;
	default:
		break;
	}
}

bool TextureDrawer3D::isMouseInsideModelCanvas(int x, int y)
{

	return x >= modelCanvasX && x <= (modelCanvasX + modelCanvasSize) &&
		y >= modelCanvasY && y <= (modelCanvasY + modelCanvasSize);
}

void TextureDrawer3D::draw()
{	
	if (selectedShader != ShaderType::none) 
    {
		cam.begin();
		ofEnableDepthTest();
		ofEnableLighting();
		light.enable();
		shader.begin();
		drawModel();
		cam.end();
		shader.end();

		light.disable();
		ofDisableLighting();
		ofDisableDepthTest();
	}
	else 
	{
		ofEnableDepthTest();

		light.enable();

		cam.begin();
		drawModel();
		cam.end();

		light.disable();

		ofDisableDepthTest();
	}
}

void TextureDrawer3D::drawBoiteDelimitationModel()
{
	ofPoint sceneMax = model.getSceneMax();
	ofPoint sceneMin = model.getSceneMin();
	ofPoint sceneCenter = model.getSceneCenter();

	float scaling = model.getNormalizedScale() * modelScale;

	ofPoint tailleBoiteDelimitation = ofPoint((sceneMax.x - sceneMin.x) * scaling, (sceneMax.y - sceneMin.y) * scaling, (sceneMax.z - sceneMin.z) * scaling);
	
	ofPoint positionModel = model.getPosition();
	ofPoint positionBox = ofPoint(positionModel.x - (sceneCenter.x * scaling), positionModel.y - (sceneCenter.y * scaling), positionModel.z - (sceneCenter.z * scaling));
	ofNoFill();
	ofSetLineWidth(7);
	ofSetColor(0, 255, 0);
	ofDrawBox(positionBox.x, positionBox.y, positionBox.z, tailleBoiteDelimitation.x, tailleBoiteDelimitation.y, tailleBoiteDelimitation.z);
}

void TextureDrawer3D::applyLambertShader()
{
	// Pris de l'exemple 4.12 du professeur
	model.disableMaterials();
	// configuration de la lumi�re
	light.setPointLight();
	light.setDiffuseColor(255);
	light.setGlobalPosition(centerX, centerY, 255.0f);

	// passer les attributs uniformes du shader
	shader.begin();
	shader.setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
	shader.setUniform3f("color_diffuse", modelColor.r / 255.0f, modelColor.g / 255.0f, modelColor.b / 255.0f);
	shader.setUniform3f("light_position", glm::vec4(light.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));

	shader.end();
}

void TextureDrawer3D::applyNoiseShader()
{
	// Pris d'un exemple d'openFrameworks sur les shaders
	model.disableMaterials();
	shader.begin();

	shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1);
	shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18);

	shader.end();
}

void TextureDrawer3D::drawModel()
{
	switch (selectedType)
	{
	case ModelType::model:
		model.drawFaces();
		if(boiteDelimitation)
			drawBoiteDelimitationModel();
		break;
	case ModelType::box:
		if (selectedShader == ShaderType::none) {
			material.begin();
			box.enableColors();
			box.enableNormals();
			box.enableTextures();
			box.draw(OF_MESH_FILL);
			material.end();
			if (boiteDelimitation)
			{
				float size = box.getDepth() * box.getGlobalScale().x;
				ofNoFill();
				ofSetLineWidth(7);
				ofSetColor(0, 255, 0);
				ofDrawBox(box.getPosition(), size, size, size);
			}
		}
		else {
			box.drawFaces();
			if (boiteDelimitation)
			{
				float size = box.getDepth() * box.getGlobalScale().x;
				ofNoFill();
				ofSetLineWidth(7);
				ofSetColor(0, 255, 0);
				ofDrawBox(box.getPosition(), size, size, size);
			}
		}
		
		break;
	case ModelType::cone:
		if (selectedShader == ShaderType::none) {
			material.begin();
			cone.enableColors();
			cone.enableNormals();
			cone.enableTextures();
			cone.draw(OF_MESH_FILL);
			material.end();			
			if (boiteDelimitation)
			{
				float sizeBase = cone.getRadius() * 2 * cone.getGlobalScale().x;
				ofNoFill();
				ofSetLineWidth(7);
				ofSetColor(0, 255, 0);
				ofDrawBox(cone.getPosition(), sizeBase, cone.getHeight() * cone.getGlobalScale().x, sizeBase);
			}
		}
		else {
			cone.drawFaces();
			if (boiteDelimitation)
			{
				float sizeBase = cone.getRadius() * 2 * cone.getGlobalScale().x;
				ofNoFill();
				ofSetLineWidth(7);
				ofSetColor(0, 255, 0);
				ofDrawBox(cone.getPosition(), sizeBase, cone.getHeight() * cone.getGlobalScale().x, sizeBase);
			}
		}
		
		break;
	case ModelType::sphere:

		if (selectedShader == ShaderType::none) {
			material.begin();
			sphere.enableColors();
			sphere.enableNormals();
			sphere.enableTextures();
			sphere.draw(OF_MESH_FILL);
			material.end();
			
			if (boiteDelimitation)
			{
				float size = sphere.getRadius() * 2 * sphere.getGlobalScale().x;
				ofNoFill();
				ofSetLineWidth(7);
				ofSetColor(0, 255, 0);
				ofDrawBox(sphere.getPosition(), size, size, size);
			}

		}
		else {
			sphere.drawFaces();
			if (boiteDelimitation)
			{
				float size = sphere.getRadius() * 2 * sphere.getGlobalScale().x;
				ofNoFill();
				ofSetLineWidth(7);
				ofSetColor(0, 255, 0);
				ofDrawBox(sphere.getPosition(), size, size, size);
			}
		}
		
		break;
	case ModelType::cylinder:
		if (selectedShader == ShaderType::none) {
			material.begin();
			cylinder.enableColors();
			cylinder.enableNormals();
			cylinder.enableTextures();
			cylinder.draw(OF_MESH_FILL);
			material.end();
			if (boiteDelimitation)
			{
				float sizeBase = cylinder.getRadius() * 2 * cylinder.getGlobalScale().x;
				ofNoFill();
				ofSetLineWidth(7);
				ofSetColor(0, 255, 0);
				ofDrawBox(cylinder.getPosition(), sizeBase, cylinder.getHeight() * cylinder.getGlobalScale().x, sizeBase);
			}
		}
		else {
			cylinder.drawFaces();
			if (boiteDelimitation)
			{
				float sizeBase = cylinder.getRadius() * 2 * cylinder.getGlobalScale().x;
				ofNoFill();
				ofSetLineWidth(7);
				ofSetColor(0, 255, 0);
				ofDrawBox(cylinder.getPosition(), sizeBase, cylinder.getHeight() * cylinder.getGlobalScale().x, sizeBase);
			}
		}
		
		break;
	default:
		break;
	}
}

void TextureDrawer3D::resetCamera()
{
	cam.reset();
	cam.setControlArea(ofRectangle(modelCanvasX, modelCanvasY, modelCanvasSize, modelCanvasSize));
	cam.setTarget(glm::vec3(centerX, centerY, 90));
	cam.setupPerspective(true, 60, 0, 0, glm::vec2(-0.4, -0.1));
	cam.setDistance(700);
}

void TextureDrawer3D::selectSphereType()
{
	selectedType = ModelType::sphere;
}
void TextureDrawer3D::selectCylinderType()
{
	selectedType = ModelType::cylinder;
}
void TextureDrawer3D::selectBoxType()
{
	selectedType = ModelType::box;
}
void TextureDrawer3D::selectConeType()
{
	selectedType = ModelType::cone;
}
void TextureDrawer3D::selectModelType()
{
	selectedType = ModelType::model;
}
