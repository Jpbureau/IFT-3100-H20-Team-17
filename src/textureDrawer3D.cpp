#include "textureDrawer3D.h"

void TextureDrawer3D::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);

	model.loadModel("teapot.obj");

	mesh = model.getMesh(0);
	model.setPosition(centerX, centerY, 90);

	cam.setTarget(glm::vec3(centerX, centerY, 90));
	cam.setDistance(700);
}

void TextureDrawer3D::update()
{
	model.disableMaterials();
	model.setScale(modelScale, modelScale, modelScale);
	model.setPosition(centerX, centerY, 90);

	if (useRotationAnimation)
		model.setRotation(0, ofGetFrameNum() * rotationSpeed, 0.0f, 1.0f, 0.0f);
	if (useLevitationAnimation) {
		model.setPosition(centerX, centerY + 30 * sin(ofGetFrameNum() / waveIntensity), 90);
	}

	//shader.begin();
	////we want to pass in some varrying values to animate our type / color 
	//shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1);
	//shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18);

	//shader.end();


}

void TextureDrawer3D::importModel(ofxAssimpModelLoader& model)
{
	this->model = model;
	model.setPosition(centerX, centerY, 0);
}

void TextureDrawer3D::updateColors(ofColor color)
{
	modelColor = color;
}

void TextureDrawer3D::updateAnimationParameters(float rotationSpeed, float waveIntensity, bool rotationAnimation, bool waveAnimation)
{
	this->rotationSpeed = rotationSpeed;
	this->waveIntensity= waveIntensity;
	this->useRotationAnimation = rotationAnimation;
	this->useLevitationAnimation = waveAnimation;
}

void TextureDrawer3D::draw()
{
	cam.begin();
	ofEnableDepthTest();
	ofEnableLighting();
	light.enable();
	shader.begin();
	model.draw(OF_MESH_FILL);
	cam.end();
	shader.end();

	light.disable();
	ofDisableLighting();
	ofDisableDepthTest();
}

void TextureDrawer3D::drawBoiteDelimitation(ofPoint point, float width, float height, float depth)
{
	ofSetLineWidth(5);
	ofSetColor(51);
	ofDrawBox(point.x, point.y, point.z, width, height, depth);
}

void TextureDrawer3D::applyLambertShader()
{
	// configuration de la lumière
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
