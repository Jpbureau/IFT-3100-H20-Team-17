#include "textureDrawer3D.h"

void TextureDrawer3D::setup()
{
	fboTexture3D.allocate(drawingCanvasSize, drawingCanvasSize, GL_RGBA);
	fboTexture3D.begin();
	ofClear(255, 255);
	fboTexture3D.end();

	model.loadModel("teapot.obj");
	//vbo = meshHelper.vbo();
	mesh = model.getMesh(0);
}

void TextureDrawer3D::update()
{

}

void TextureDrawer3D::draw()
{
	ofSetColor(255);
	fboTexture3D.draw(drawingCanvasX + drawingCanvasSize + 10, drawingCanvasY);
	fboTexture3D.begin();
	drawBoiteDelimitation(ofPoint(64, 64, 0), 64, 64, 64);
	fboTexture3D.end();
}

void TextureDrawer3D::drawBoiteDelimitation(ofPoint point, float width, float height, float depth)
{
	ofSetLineWidth(5);
	ofSetColor(51);
	ofDrawBox(point.x, point.y, point.z, width, height, depth);
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
