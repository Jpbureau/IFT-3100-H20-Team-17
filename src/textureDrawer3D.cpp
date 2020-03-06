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

	mesh = model.getMesh(0);
	model.setPosition(centerX, centerY, 90);
	shader.load("lambert_330_vs.glsl", "lambert_330_fs.glsl");

	cam.setControlArea(ofRectangle(modelCanvasX, modelCanvasY, modelCanvasSize, modelCanvasSize));
	cam.setTarget(glm::vec3(centerX, centerY, 90));
	cam.setupPerspective(true, 60, 0, 0, glm::vec2( -0.4 , -0.1));
	cam.setDistance(700);

	//vbo = meshHelper.vbo();

	geometricRegularPrimitive.type = GeometricRegularPrimitiveType::none;
	geometricOtherPrimitive.type = GeometricOtherPrimitiveType::none;
	geometricOtherPrimitiveSelectedType = GeometricOtherPrimitiveType::none;
	geometricRegularPrimitiveSelectedType = GeometricRegularPrimitiveType::none;

	geometricRegularPrimitive.selected = false;
	geometricOtherPrimitive.selected = false;

	geometricRegularPrimitive.stroke_width = 1;
	geometricOtherPrimitive.stroke_width = 1;

}

void TextureDrawer3D::update()
{
	model.setScale(modelScale, modelScale, modelScale);
	model.setPosition(centerX, centerY, 90);

	if (useRotationAnimation)
		model.setRotation(0, ofGetFrameNum() * rotationSpeed, 0.0f, 1.0f, 0.0f);
	if (useLevitationAnimation) {
		model.setPosition(centerX, centerY + 30 * sin(ofGetFrameNum() / waveIntensity), 90);
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

	if (geometricRegularPrimitive.selected)
	{
		geometricRegularPrimitive.radius = geometricPrimitiveRadius;

		geometricRegularPrimitive.position[0] = geometricPrimitiveXCoordinate;
		geometricRegularPrimitive.position[1] = geometricPrimitiveYCoordinate;
		geometricRegularPrimitive.position[2] = geometricPrimitiveZCoordinate;

		geometricRegularPrimitive.fill_color[0] = geometricPrimitiveFillColor_r;
		geometricRegularPrimitive.fill_color[1] = geometricPrimitiveFillColor_g;
		geometricRegularPrimitive.fill_color[2] = geometricPrimitiveFillColor_b;
		geometricRegularPrimitive.fill_color[3] = geometricPrimitiveFillColor_a;

		geometricRegularPrimitive.stroke_color[0] = geometricPrimitiveStrokeColor_r;
		geometricRegularPrimitive.stroke_color[1] = geometricPrimitiveStrokeColor_g;
		geometricRegularPrimitive.stroke_color[2] = geometricPrimitiveStrokeColor_b;
		geometricRegularPrimitive.stroke_color[3] = geometricPrimitiveStrokeColor_a;
	}

	if (geometricOtherPrimitive.selected)
	{
		geometricOtherPrimitive.nbSides = geometricPrimitiveNbSides;

		geometricOtherPrimitive.position[0] = geometricPrimitiveXCoordinate;
		geometricOtherPrimitive.position[1] = geometricPrimitiveYCoordinate;
		geometricOtherPrimitive.position[2] = geometricPrimitiveZCoordinate;

		geometricOtherPrimitive.heigth = geometricPrimitiveHeight;
		geometricOtherPrimitive.width = geometricPrimitiveWidth;
		geometricOtherPrimitive.depth = geometricPrimitiveDepth;

		geometricOtherPrimitive.fill_color[0] = geometricPrimitiveFillColor_r;
		geometricOtherPrimitive.fill_color[1] = geometricPrimitiveFillColor_g;
		geometricOtherPrimitive.fill_color[2] = geometricPrimitiveFillColor_b;
		geometricOtherPrimitive.fill_color[3] = geometricPrimitiveFillColor_a;

		geometricOtherPrimitive.stroke_color[0] = geometricPrimitiveStrokeColor_r;
		geometricOtherPrimitive.stroke_color[1] = geometricPrimitiveStrokeColor_g;
		geometricOtherPrimitive.stroke_color[2] = geometricPrimitiveStrokeColor_b;
		geometricOtherPrimitive.stroke_color[3] = geometricPrimitiveStrokeColor_a;
	}

}

void TextureDrawer3D::addGeometricPrimitive()
{
	if (geometricRegularPrimitiveSelectedType != GeometricRegularPrimitiveType::none)
	{
		geometricRegularPrimitive.type = geometricRegularPrimitiveSelectedType;

		geometricRegularPrimitive.radius = geometricPrimitiveRadius;

		geometricRegularPrimitive.position[0] = geometricPrimitiveXCoordinate;
		geometricRegularPrimitive.position[1] = geometricPrimitiveYCoordinate;
		geometricRegularPrimitive.position[2] = geometricPrimitiveZCoordinate;

		geometricRegularPrimitive.fill_color[0] = geometricPrimitiveFillColor_r;
		geometricRegularPrimitive.fill_color[1] = geometricPrimitiveFillColor_g;
		geometricRegularPrimitive.fill_color[2] = geometricPrimitiveFillColor_b;
		geometricRegularPrimitive.fill_color[3] = geometricPrimitiveFillColor_a;

		geometricRegularPrimitive.stroke_color[0] = geometricPrimitiveStrokeColor_r;
		geometricRegularPrimitive.stroke_color[1] = geometricPrimitiveStrokeColor_g;
		geometricRegularPrimitive.stroke_color[2] = geometricPrimitiveStrokeColor_b;
		geometricRegularPrimitive.stroke_color[3] = geometricPrimitiveStrokeColor_a;

	}

	if (geometricOtherPrimitiveSelectedType != GeometricOtherPrimitiveType::none)
	{
		geometricOtherPrimitive.type = geometricOtherPrimitiveSelectedType;

		geometricOtherPrimitive.nbSides = geometricPrimitiveNbSides;

		geometricOtherPrimitive.position[0] = geometricPrimitiveXCoordinate;
		geometricOtherPrimitive.position[1] = geometricPrimitiveYCoordinate;
		geometricOtherPrimitive.position[2] = geometricPrimitiveZCoordinate;

		geometricOtherPrimitive.heigth = geometricPrimitiveHeight;
		geometricOtherPrimitive.width = geometricPrimitiveWidth;
		geometricOtherPrimitive.depth = geometricPrimitiveDepth;

		geometricOtherPrimitive.fill_color[0] = geometricPrimitiveFillColor_r;
		geometricOtherPrimitive.fill_color[1] = geometricPrimitiveFillColor_g;
		geometricOtherPrimitive.fill_color[2] = geometricPrimitiveFillColor_b;
		geometricOtherPrimitive.fill_color[3] = geometricPrimitiveFillColor_a;

		geometricOtherPrimitive.stroke_color[0] = geometricPrimitiveStrokeColor_r;
		geometricOtherPrimitive.stroke_color[1] = geometricPrimitiveStrokeColor_g;
		geometricOtherPrimitive.stroke_color[2] = geometricPrimitiveStrokeColor_b;
		geometricOtherPrimitive.stroke_color[3] = geometricPrimitiveStrokeColor_a;
	}

}

void TextureDrawer3D::importModel(ofxAssimpModelLoader& model)
{
	this->model = model;
	model.setPosition(centerX, centerY, 0);
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
	if (selectedShader == ShaderType::lambert) 
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
	else 
  {
		ofEnableDepthTest();

		light.enable();

		cam.begin();
		ofPushMatrix();

		ofTranslate( 0, 0);
		ofColor(255, 255);
		model.drawFaces();

		ofPopMatrix();
		cam.end();

		light.disable();

		ofDisableDepthTest();
	}

	ofSetColor(255);
	fboTexture3D.draw(modelCanvasX + modelCanvasSize + 10, modelCanvasY);
	fboTexture3D.begin();
	drawBoiteDelimitation(ofPoint(64, 64, 0), 64, 64, 64);

	ofFill();

	ofSetLineWidth(geometricRegularPrimitive.stroke_width);
	ofSetColor(
		geometricRegularPrimitive.fill_color[0],
		geometricRegularPrimitive.fill_color[1],
		geometricRegularPrimitive.fill_color[2]);
	
	switch (geometricRegularPrimitive.type)
	{
	case GeometricRegularPrimitiveType::tetrahedron:
		draw_tetrahedron(
			geometricRegularPrimitive.radius,
			geometricRegularPrimitive.position[0],
			geometricRegularPrimitive.position[1],
			geometricRegularPrimitive.position[2]);
		ofNoFill();
		ofSetColor(
			geometricRegularPrimitive.stroke_color[0],
			geometricRegularPrimitive.stroke_color[1],
			geometricRegularPrimitive.stroke_color[2]);
		draw_tetrahedron(
			geometricRegularPrimitive.radius,
			geometricRegularPrimitive.position[0],
			geometricRegularPrimitive.position[1],
			geometricRegularPrimitive.position[2]);
		break;

	case GeometricRegularPrimitiveType::hexahedron:
		draw_hexahedron(
			geometricRegularPrimitive.radius,
			geometricRegularPrimitive.position[0],
			geometricRegularPrimitive.position[1],
			geometricRegularPrimitive.position[2]);
		ofNoFill();
		ofSetColor(
			geometricRegularPrimitive.stroke_color[0],
			geometricRegularPrimitive.stroke_color[1],
			geometricRegularPrimitive.stroke_color[2]);
		draw_hexahedron(
			geometricRegularPrimitive.radius,
			geometricRegularPrimitive.position[0],
			geometricRegularPrimitive.position[1],
			geometricRegularPrimitive.position[2]);
		break;

	case GeometricRegularPrimitiveType::octahedron:
		draw_octahedron(
			geometricRegularPrimitive.radius,
			geometricRegularPrimitive.position[0],
			geometricRegularPrimitive.position[1],
			geometricRegularPrimitive.position[2]);
		ofNoFill();
		ofSetColor(
			geometricRegularPrimitive.stroke_color[0],
			geometricRegularPrimitive.stroke_color[1],
			geometricRegularPrimitive.stroke_color[2]);
		draw_octahedron(
			geometricRegularPrimitive.radius,
			geometricRegularPrimitive.position[0],
			geometricRegularPrimitive.position[1],
			geometricRegularPrimitive.position[2]);
		break;

	case GeometricRegularPrimitiveType::dodecahedron:
		draw_dodecahedron(
			geometricRegularPrimitive.radius,
			geometricRegularPrimitive.position[0],
			geometricRegularPrimitive.position[1],
			geometricRegularPrimitive.position[2]);
		ofNoFill();
		ofSetColor(
			geometricRegularPrimitive.stroke_color[0],
			geometricRegularPrimitive.stroke_color[1],
			geometricRegularPrimitive.stroke_color[2]);
		draw_dodecahedron(
			geometricRegularPrimitive.radius,
			geometricRegularPrimitive.position[0],
			geometricRegularPrimitive.position[1],
			geometricRegularPrimitive.position[2]);
		break;

	case GeometricRegularPrimitiveType::icosahedron:
		draw_icosahedron(
			geometricRegularPrimitive.radius,
			geometricRegularPrimitive.position[0],
			geometricRegularPrimitive.position[1],
			geometricRegularPrimitive.position[2]);
		ofNoFill();
		ofSetColor(
			geometricRegularPrimitive.stroke_color[0],
			geometricRegularPrimitive.stroke_color[1],
			geometricRegularPrimitive.stroke_color[2]);
		draw_icosahedron(
			geometricRegularPrimitive.radius,
			geometricRegularPrimitive.position[0],
			geometricRegularPrimitive.position[1],
			geometricRegularPrimitive.position[2]);
		break;

	case GeometricRegularPrimitiveType::sphere:
		draw_sphere(
			geometricRegularPrimitive.radius,
			geometricRegularPrimitive.position[0],
			geometricRegularPrimitive.position[1],
			geometricRegularPrimitive.position[2]);
		
		break;

	default:
		break;
	}

	ofFill();
	ofSetLineWidth(geometricOtherPrimitive.stroke_width);
	ofSetColor(
		geometricOtherPrimitive.fill_color[0],
		geometricOtherPrimitive.fill_color[1],
		geometricOtherPrimitive.fill_color[2]);

	switch (geometricOtherPrimitive.type)
	{
	case GeometricOtherPrimitiveType::ellipse:
		draw_ellipse(
			geometricOtherPrimitive.width,
			geometricOtherPrimitive.heigth,
			geometricOtherPrimitive.depth,
			geometricOtherPrimitive.position[0],
			geometricOtherPrimitive.position[1],
			geometricOtherPrimitive.position[2]);
		break;

	case GeometricOtherPrimitiveType::polygon:
		draw_polygon(
			geometricOtherPrimitive.width,
			geometricOtherPrimitive.heigth,
			geometricOtherPrimitive.depth,
			geometricOtherPrimitive.position[0],
			geometricOtherPrimitive.position[1],
			geometricOtherPrimitive.position[2],
			geometricOtherPrimitive.nbSides);
		ofNoFill();
		ofSetColor(
			geometricOtherPrimitive.stroke_color[0],
			geometricOtherPrimitive.stroke_color[1],
			geometricOtherPrimitive.stroke_color[2]);
		draw_polygon(
			geometricOtherPrimitive.width,
			geometricOtherPrimitive.heigth,
			geometricOtherPrimitive.depth,
			geometricOtherPrimitive.position[0],
			geometricOtherPrimitive.position[1],
			geometricOtherPrimitive.position[2],
			geometricOtherPrimitive.nbSides);
		break;

	case GeometricOtherPrimitiveType::cylinder:
		draw_cylinder(
			geometricOtherPrimitive.width,
			geometricOtherPrimitive.heigth,
			geometricOtherPrimitive.depth,
			geometricOtherPrimitive.position[0],
			geometricOtherPrimitive.position[1],
			geometricOtherPrimitive.position[2]);
		ofNoFill();
		ofSetColor(
			geometricOtherPrimitive.stroke_color[0],
			geometricOtherPrimitive.stroke_color[1],
			geometricOtherPrimitive.stroke_color[2]);
		draw_cylinder(
			geometricOtherPrimitive.width,
			geometricOtherPrimitive.heigth,
			geometricOtherPrimitive.depth,
			geometricOtherPrimitive.position[0],
			geometricOtherPrimitive.position[1],
			geometricOtherPrimitive.position[2]);
		break;

	case GeometricOtherPrimitiveType::rectangle:
		draw_rectangle(
			geometricOtherPrimitive.width,
			geometricOtherPrimitive.heigth,
			geometricOtherPrimitive.depth,
			geometricOtherPrimitive.position[0],
			geometricOtherPrimitive.position[1],
			geometricOtherPrimitive.position[2]);
		ofNoFill();
		ofSetColor(
			geometricOtherPrimitive.stroke_color[0],
			geometricOtherPrimitive.stroke_color[1],
			geometricOtherPrimitive.stroke_color[2]);
		draw_rectangle(
			geometricOtherPrimitive.width,
			geometricOtherPrimitive.heigth,
			geometricOtherPrimitive.depth,
			geometricOtherPrimitive.position[0],
			geometricOtherPrimitive.position[1],
			geometricOtherPrimitive.position[2]);
		break;

	case GeometricOtherPrimitiveType::cone:
		draw_cone(
			geometricOtherPrimitive.width,
			geometricOtherPrimitive.heigth,
			geometricOtherPrimitive.depth,
			geometricOtherPrimitive.position[0],
			geometricOtherPrimitive.position[1],
			geometricOtherPrimitive.position[2]);
		ofNoFill();
		ofSetColor(
			geometricOtherPrimitive.stroke_color[0],
			geometricOtherPrimitive.stroke_color[1],
			geometricOtherPrimitive.stroke_color[2]);
		draw_cone(
			geometricOtherPrimitive.width,
			geometricOtherPrimitive.heigth,
			geometricOtherPrimitive.depth,
			geometricOtherPrimitive.position[0],
			geometricOtherPrimitive.position[1],
			geometricOtherPrimitive.position[2]);
		break;

	default:
		break;
	}

	fboTexture3D.end();
}

void TextureDrawer3D::drawBoiteDelimitation(ofPoint point, float width, float height, float depth)
{
	ofNoFill();
	ofSetLineWidth(5);
	ofSetColor(51);
	ofDrawBox(point.x, point.y, point.z, width, height, depth);
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

void TextureDrawer3D::draw_tetrahedron(GLfloat radius, GLfloat x, GLfloat y, GLfloat z) const
{
	//x = 2, y = 2, z = 2, radius = 2

	//x1 + x2 + x3 + x4 = 8, y1 + y2 + y3 + y4 = 8, z1 + z2 + z3+ z4 = 8
	//2, 4, 2 //6, 4, 6
	//0.67, 1.33, 1.33 //5.33, 2.66, 4.66
	//3.33, 1.33, 1.33 //2, 1.33, 3.33
	//2, 1.33, 3.33 //0, 0, 0

	//(radius / 1.5) = 1.33
	//(radius / 3) = 0.66


	glm::vec3 pointHaut = {x, y + radius, z};
	glm::vec3 pointGauche= { x - (radius / 1.5), y - (radius/3), z - (radius / 3) };
	glm::vec3 pointDroite= { x + (radius / 1.5), y - (radius/3), z - (radius / 3) };
	glm::vec3 pointFond= {x, y - (radius/3), z + (radius / 1.5) };

	//Je fais quoi ensuite?

}

void TextureDrawer3D::draw_hexahedron(GLfloat radius, GLfloat x, GLfloat y, GLfloat z) const
{
	
	float cubeDimension = sqrt((radius*2)*(radius*2)/3);
	ofDrawBox(x, y, z, cubeDimension, cubeDimension, cubeDimension);
}

void TextureDrawer3D::draw_octahedron(GLfloat radius, GLfloat x, GLfloat y, GLfloat z) const
{

}

void TextureDrawer3D::draw_dodecahedron(GLfloat radius, GLfloat x, GLfloat y, GLfloat z) const
{

}

void TextureDrawer3D::draw_icosahedron(GLfloat radius, GLfloat x, GLfloat y, GLfloat z) const
{

}

void TextureDrawer3D::draw_sphere(GLfloat radius, GLfloat x, GLfloat y, GLfloat z) const
{

	ofDrawSphere(x, y, z, radius);
}

void TextureDrawer3D::draw_ellipse(GLfloat width, GLfloat height, GLfloat depth, GLfloat x, GLfloat y, GLfloat z) const
{
	
}

void TextureDrawer3D::draw_polygon(GLfloat width, GLfloat height, GLfloat depth, GLfloat x, GLfloat y, GLfloat z, GLubyte nbSides) const
{

}

void TextureDrawer3D::draw_cylinder(GLfloat width, GLfloat height, GLfloat depth, GLfloat x, GLfloat y, GLfloat z) const
{
	ofDrawCylinder(x, y, z, width / 2, height);
}

void TextureDrawer3D::draw_rectangle(GLfloat width, GLfloat height, GLfloat depth, GLfloat x, GLfloat y, GLfloat z) const
{
	ofDrawBox(x, y, z, width, height, depth);
}

void TextureDrawer3D::draw_cone(GLfloat width, GLfloat height, GLfloat depth, GLfloat x, GLfloat y, GLfloat z) const
{
	//Ceci ne peut pas faire de cônes elliptique
	ofDrawCone(x, y, z, width / 2, height);
}


void TextureDrawer3D::updateColors(ofColor stroke, ofColor fill)
{
	geometricPrimitiveStrokeColor_r = stroke.r;
	geometricPrimitiveStrokeColor_g = stroke.g;
	geometricPrimitiveStrokeColor_b = stroke.b;
	geometricPrimitiveStrokeColor_a = stroke.a;

	geometricPrimitiveFillColor_r = fill.r;
	geometricPrimitiveFillColor_g = fill.g;
	geometricPrimitiveFillColor_b = fill.b;
	geometricPrimitiveFillColor_a = fill.a;
}

void TextureDrawer3D::updateCoordinates(GLfloat x, GLfloat y, GLfloat z)
{
	geometricPrimitiveXCoordinate = x;
	geometricPrimitiveYCoordinate = y;
	geometricPrimitiveZCoordinate = z;
}

void TextureDrawer3D::updateRadius(float newRadius)
{
	geometricPrimitiveRadius = newRadius;
}

void TextureDrawer3D::updateDimensions(GLfloat width, GLfloat height, GLfloat depth)
{
	geometricPrimitiveHeight = width;
	geometricPrimitiveWidth = height;
	geometricPrimitiveDepth = depth;
}

void TextureDrawer3D::updateNbSides(GLubyte nbSides)
{
	geometricPrimitiveNbSides = nbSides;
}

void TextureDrawer3D::selectTetrahedronType()
{
	geometricOtherPrimitiveSelectedType = GeometricOtherPrimitiveType::none;
	geometricRegularPrimitiveSelectedType = GeometricRegularPrimitiveType::tetrahedron;
}
void TextureDrawer3D::selectHexahedronType()
{
	geometricOtherPrimitiveSelectedType = GeometricOtherPrimitiveType::none;
	geometricRegularPrimitiveSelectedType = GeometricRegularPrimitiveType::hexahedron;
}
void TextureDrawer3D::selectOctahedronType()
{
	geometricOtherPrimitiveSelectedType = GeometricOtherPrimitiveType::none;
	geometricRegularPrimitiveSelectedType = GeometricRegularPrimitiveType::octahedron;
}
void TextureDrawer3D::selectDodecahedronType()
{
	geometricOtherPrimitiveSelectedType = GeometricOtherPrimitiveType::none;
	geometricRegularPrimitiveSelectedType = GeometricRegularPrimitiveType::dodecahedron;
}
void TextureDrawer3D::selectIcosahedronType()
{
	geometricOtherPrimitiveSelectedType = GeometricOtherPrimitiveType::none;
	geometricRegularPrimitiveSelectedType = GeometricRegularPrimitiveType::icosahedron;
}
void TextureDrawer3D::selectSphereType()
{
	geometricOtherPrimitiveSelectedType = GeometricOtherPrimitiveType::none;
	geometricRegularPrimitiveSelectedType = GeometricRegularPrimitiveType::sphere;
}
void TextureDrawer3D::selectEllipseType()
{
	geometricOtherPrimitiveSelectedType = GeometricOtherPrimitiveType::ellipse;
	geometricRegularPrimitiveSelectedType = GeometricRegularPrimitiveType::none;
}
void TextureDrawer3D::selectPolygonType()
{
	geometricOtherPrimitiveSelectedType = GeometricOtherPrimitiveType::polygon;
	geometricRegularPrimitiveSelectedType = GeometricRegularPrimitiveType::none;
}
void TextureDrawer3D::selectCylinderType()
{
	geometricOtherPrimitiveSelectedType = GeometricOtherPrimitiveType::cylinder;
	geometricRegularPrimitiveSelectedType = GeometricRegularPrimitiveType::none;
}
void TextureDrawer3D::selectRectangleType()
{
	geometricOtherPrimitiveSelectedType = GeometricOtherPrimitiveType::rectangle;
	geometricRegularPrimitiveSelectedType = GeometricRegularPrimitiveType::none;
}
void TextureDrawer3D::selectConeType()
{
	geometricOtherPrimitiveSelectedType = GeometricOtherPrimitiveType::cone;
	geometricRegularPrimitiveSelectedType = GeometricRegularPrimitiveType::none;
}