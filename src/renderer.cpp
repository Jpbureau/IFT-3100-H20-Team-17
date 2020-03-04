#include "renderer.h"

void Renderer::setup()
{
	cursor.setup(drawingCanvasX, drawingCanvasY, drawingCanvasSize);
	cursor.setCursorImage(none);

	textureDrawer.setup(drawingCanvasX, drawingCanvasY, drawingCanvasSize);
	fboTexture.allocate(drawingCanvasSize, drawingCanvasSize, GL_RGBA);
	fboTexture.begin();
	ofClear(255, 255);
	ofSetColor(255);
	fboTexture.end();

	fboTexture3D.allocate(drawingCanvasSize, drawingCanvasSize, GL_RGBA);
	fboTexture3D.begin();
	ofClear(255, 255);
	fboTexture3D.end();

	fileManagerGui.setup();
	canvas2dGui.setup(drawingCanvasY);

	canvas3DGui.setup();
	
	//Il faudra ajuster la position de départ exacte plus tard
	colorHistogram.setup();
	colorHistogramGui.setup(10, 560);

	//ofSetFrameRate(60);
	//ofEnableDepthTest();
	ofEnableLighting();

	mesh_render_mode = MeshRenderMode::fill;

	light.setAmbientColor(ofColor(0, 255, 0));
	light.setDiffuseColor(ofColor(255, 255, 255));
	light.setPosition(0.0f, 0.0f, 1000.0f);
	light.enable();

	teapot.loadModel("teapot.obj");
	//vbo = meshHelper.vbo();
	mesh = teapot.getMesh(0);
}

void Renderer::update()
{
	canvas2dGui.update();
	textureDrawer.update();
	cursor.update();

	//À implémenter plus tard: Faire l'update automatique seulement lorsqu'il y a un changement, ou une fois à toutes les x frames
	if (colorHistogramGui.getUpdateHistogram())
	{
		//Vérifier les dimensions...
		image.grabScreen(drawingCanvasX, drawingCanvasY, drawingCanvasSize, drawingCanvasSize);
		ofPixels pixels = image.getPixels();
		colorHistogramGui.update(pixels);
		//colorHistogram.update();
	}
	
}

void Renderer::draw()
{
	ofSetBackgroundColor(canvas2dGui.backGroundColor);

	ofSetColor(255);
	fboTexture.draw(drawingCanvasX, drawingCanvasY);
	fboTexture3D.draw(drawingCanvasX + drawingCanvasSize + 10, drawingCanvasY);
	/*ofBackgroundGradient(ofColor::white, ofColor::gray);
	ofSetColor(255, 130, 0);
	ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, 50);*/

	/*if (image.isAllocated()) {
		ofSetColor(255);
		image.draw(0, 0, ofGetWidth(), ofGetHeight());
	}*/
	textureDrawer.draw();
	cursor.draw();
	fileManagerGui.draw();
	canvas2dGui.draw();
	canvas3DGui.draw();
	
	if (colorHistogramGui.getHistogramShown())
	{
		colorHistogram.draw();
	}
	colorHistogramGui.draw();

	//J'ajoute mon code ici
	fboTexture3D.begin();
	//drawBoiteDelimitation(ofPoint(64, 64, 0), 64, 64, 64);
	teapot.draw(OF_MESH_FILL);
	fboTexture3D.end();

	// dessiner une instance du teapot
	/*switch (mesh_render_mode)
	{
	case MeshRenderMode::fill:
		teapot.draw(OF_MESH_FILL);
		break;

	case MeshRenderMode::wireframe:
		teapot.draw(OF_MESH_WIREFRAME);
		break;

	case MeshRenderMode::vertex:
		teapot.draw(OF_MESH_POINTS);
		break;
	}*/
}

void Renderer::mousePressed(int x, int y)
{
	textureDrawer.mouse_pressed_posX = x;
	textureDrawer.mouse_pressed_posY = y;
	textureDrawer.selectShape(x, y);
}

void Renderer::mouseReleased(int x, int y)
{
	textureDrawer.mouse_current_posX = x;
	textureDrawer.mouse_current_posY = y;
	textureDrawer.add_vector_shape();
}



void Renderer::drawBoiteDelimitation(ofPoint point, float width, float height, float depth)
{
	ofSetLineWidth(5);
	ofSetColor(51);
	ofDrawBox(point.x, point.y, point.z, width, height, depth);
}

void Renderer::calculerBoiteDelimitation()
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