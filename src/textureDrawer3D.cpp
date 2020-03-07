#include "textureDrawer3D.h"

void TextureDrawer3D::setup(int canvasPositionX, int canvasPositionY, int canvasSize)
{
	this->modelCanvasX = canvasPositionX;
	this->modelCanvasY = canvasPositionY;
	this->modelCanvasSize = canvasSize;
	this->centerX = modelCanvasX + modelCanvasSize / 2;
	this->centerY = modelCanvasY + modelCanvasSize / 2;

	ofSetLogLevel(OF_LOG_VERBOSE);

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
	mesh = model.getCurrentAnimatedMesh(0);

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
	default:
		break;
	}

	//shader.begin();
	////we want to pass in some varrying values to animate our type / color 
	//shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1);
	//shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18);

	//shader.end();

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

void TextureDrawer3D::updateShaderSelection(ShaderType selected)
{
	switch (selected)
	{
	case ShaderType::lambert:
		selectedShader = selected;
		shader.load("lambert_330_vs.glsl", "lambert_330_fs.glsl");
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

	//ofFill();
	//ofSetColor(255);
	//ofDrawRectangle(modelCanvasX, modelCanvasY, modelCanvasSize, modelCanvasSize);

	ofSetColor(255,0,0);
	ofDrawCircle( centerX, centerY, 90, 10);

	if (selectedShader == ShaderType::lambert) 
    {
		cam.begin();
		ofEnableDepthTest();
		ofEnableLighting();
		light.enable();
		shader.begin();
		drawModel();
		drawBoiteDelimitation(mesh);
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

	ofPoint positionModel = ofPoint(centerX, centerY, 90);

	

	//ofSetColor(255);
	//fboTexture3D.draw(modelCanvasX + modelCanvasSize + 10, modelCanvasY);
	//fboTexture3D.begin();

	//fboTexture3D.end();
}

void TextureDrawer3D::drawBoiteDelimitation(const ofMesh &mesh)
{
	//ofVec3f boundingWigthHeightDepth = getMeshBoundingBoxDimension(mesh);
	//glm::vec3 positionModel = glm::vec3(centerX, centerY - (boundingWigthHeightDepth.y/2), 90);
	ofPoint sceneMax = model.getSceneMax();
	ofPoint sceneMin = model.getSceneMin();
	ofPoint sceneCenter = model.getSceneCenter();

	float scaling;
	float scale = model.getScale().x;
	scaling = model.getNormalizedScale()*scale;

	ofPoint tailleBoiteDelimitation = ofPoint((sceneMax.x - sceneMin.x) * scaling, (sceneMax.y - sceneMin.y) * scaling, (sceneMax.z - sceneMin.z) * scaling);
	
	ofPoint positionModel = model.getPosition();
	ofPoint positionBox = ofPoint((sceneCenter.x * scaling) + positionModel.x, (sceneCenter.y * scaling) + positionModel.y, (sceneCenter.z * scaling)+ positionModel.z);
	cout << scaling << "\n";
	cout << positionModel.x << ", " << positionModel.y << ", " << positionModel.z << "\n";
	cout << tailleBoiteDelimitation.x << ", " << tailleBoiteDelimitation.y << ", " << tailleBoiteDelimitation.z << "\n";
	ofNoFill();
	ofSetLineWidth(7);
	ofSetColor(0, 255, 0);
	ofDrawBox(positionBox.x, positionBox.y, positionBox.z, tailleBoiteDelimitation.x, tailleBoiteDelimitation.y, tailleBoiteDelimitation.z);

}

ofVec3f TextureDrawer3D::getMeshBoundingBoxDimension(const ofMesh &mesh) {

	auto xExtremes = minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(),
		[](const ofPoint& lhs, const ofPoint& rhs) {
		return lhs.x < rhs.x;
	});
	auto yExtremes = minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(),
		[](const ofPoint& lhs, const ofPoint& rhs) {
		return lhs.y < rhs.y;
	});
	auto zExtremes = minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(),
		[](const ofPoint& lhs, const ofPoint& rhs) {
		return lhs.z < rhs.z;
	});
	float scaling;
	float scale = model.getScale().x;
	scaling = model.getNormalizedScale()*scale;
	ofVec3f dim = ofVec3f((xExtremes.second->x - xExtremes.first->x) * scaling,
						(yExtremes.second->y - yExtremes.first->y) * scaling,
						(zExtremes.second->z - zExtremes.first->z) * scaling);
	return dim;
}


void TextureDrawer3D::applyLambertShader()
{
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

void TextureDrawer3D::drawModel()
{
	switch (selectedType)
	{
	case ModelType::model:
		model.drawFaces();
		drawBoiteDelimitation(mesh);
		break;
	case ModelType::box:
		if (selectedShader == ShaderType::none) {
			material.begin();
			box.enableColors();
			box.enableNormals();
			box.enableTextures();
			box.draw(OF_MESH_FILL);
			material.end();
		}
		else {
			box.drawFaces();
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
		}
		else {
			cone.drawFaces();
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
			float rayon = sphere.getRadius();
			ofNoFill();
			ofSetLineWidth(7);
			ofSetColor(0, 255, 0);
			ofDrawBox(sphere.getPosition(), rayon*2*5, rayon*2*5, rayon*2*5);
			cout << rayon << "\n";
		}
		else {
			sphere.drawFaces();
			float rayon = sphere.getRadius();
			ofNoFill();
			ofSetLineWidth(7);
			ofSetColor(0, 255, 0);
			ofDrawBox(sphere.getPosition(), rayon * 2 * 5, rayon * 2 * 5, rayon * 2 * 5);
			cout << rayon << "\n";
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
		}
		else {
			cylinder.drawFaces();
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

void TextureDrawer3D::calculerBoiteDelimitation()
{
	std::vector<glm::vec3> vertices = mesh.getVertices();
	std::vector<glm::vec3>::iterator it;

	glm::vec3 pointGauche = vertices.at(0);
	glm::vec3 pointAvant = vertices.at(0);
	glm::vec3 pointDroit = vertices.at(0);
	glm::vec3 pointArriere = vertices.at(0);
	glm::vec3 pointDessus = vertices.at(0);
	glm::vec3 pointDessous = vertices.at(0);

	// Parcours du conteneur de vertices pour déterminer ceux qui
	// Sont le plus aux extrémités
	for (it = vertices.begin(); it != vertices.end(); ++it)
	{
		if ((*it).x < pointGauche.x)
		{
			pointGauche = *it;
		}

		if ((*it).x > pointDroit.x)
		{
			pointDroit = *it;
		}

		if ((*it).y < pointDessus.y)
		{
			pointDessus = *it;
		}

		if ((*it).y > pointDessous.y)
		{
			pointDessous = *it;
		}

		if ((*it).z < pointAvant.z)
		{
			pointAvant = *it;
		}

		if ((*it).z > pointArriere.z)
		{
			pointArriere = *it;
		}
	}

	pointSupGaucheBoite = ofPoint(pointGauche.x, pointDessus.y, pointAvant.z);
	largeurModel3D = pointDroit.x - pointGauche.x;
	hauteurModel3D = pointDessus.y - pointDessous.y;
	profondeurModel3D = pointArriere.z - pointAvant.z;
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
