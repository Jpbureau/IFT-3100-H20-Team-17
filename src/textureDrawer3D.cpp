#include "textureDrawer3D.h"

void TextureDrawer3D::setup()
{
	fboTexture3D.allocate(drawingCanvasSize, drawingCanvasSize, GL_RGBA);
	fboTexture3D.begin();
	ofClear(255, 255);
	fboTexture3D.end();

	teapot.loadModel("teapot.obj");
	//vbo = meshHelper.vbo();
	mesh = teapot.getMesh(0);

	objet3dTest1.type = GeometricRegularPrimitiveType::none;
	objet3dTest2.type = GeometricOtherPrimitiveType::none;
	geometricOtherPrimitiveSelectedType = GeometricOtherPrimitiveType::none;
	geometricRegularPrimitiveSelectedType = GeometricRegularPrimitiveType::none;
}

void TextureDrawer3D::update()
{
	//On pourrait aussi potentiellement l'activer seulement au clique d'un bouton
	if (objet3dTest1.selected) 
	{
		objet3dTest1.radius = geometricPrimitiveRadius;

		objet3dTest1.position[0] = geometricPrimitiveXCoordinate;
		objet3dTest1.position[1] = geometricPrimitiveYCoordinate;
		objet3dTest1.position[2] = geometricPrimitiveZCoordinate;

		objet3dTest1.fill_color[0] = geometricPrimitiveFillColor_r;
		objet3dTest1.fill_color[1] = geometricPrimitiveFillColor_g;
		objet3dTest1.fill_color[2] = geometricPrimitiveFillColor_b;
		objet3dTest1.fill_color[3] = geometricPrimitiveFillColor_a;

		objet3dTest1.stroke_color[0] = geometricPrimitiveStrokeColor_r;
		objet3dTest1.stroke_color[1] = geometricPrimitiveStrokeColor_g;
		objet3dTest1.stroke_color[2] = geometricPrimitiveStrokeColor_b;
		objet3dTest1.stroke_color[3] = geometricPrimitiveStrokeColor_a;
	}

	if (objet3dTest2.selected)
	{
		objet3dTest2.nbSides = geometricPrimitiveNbSides;

		objet3dTest2.position[0] = geometricPrimitiveXCoordinate;
		objet3dTest2.position[1] = geometricPrimitiveYCoordinate;
		objet3dTest2.position[2] = geometricPrimitiveZCoordinate;

		objet3dTest2.heigth = geometricPrimitiveHeight;
		objet3dTest2.width = geometricPrimitiveWidth;
		objet3dTest2.depth = geometricPrimitiveDepth;

		objet3dTest2.fill_color[0] = geometricPrimitiveFillColor_r;
		objet3dTest2.fill_color[1] = geometricPrimitiveFillColor_g;
		objet3dTest2.fill_color[2] = geometricPrimitiveFillColor_b;
		objet3dTest2.fill_color[3] = geometricPrimitiveFillColor_a;

		objet3dTest2.stroke_color[0] = geometricPrimitiveStrokeColor_r;
		objet3dTest2.stroke_color[1] = geometricPrimitiveStrokeColor_g;
		objet3dTest2.stroke_color[2] = geometricPrimitiveStrokeColor_b;
		objet3dTest2.stroke_color[3] = geometricPrimitiveStrokeColor_a;
	}

}

void TextureDrawer3D::addGeometricRegularPrimitive()
{
	
}

void TextureDrawer3D::addGeometricOtherPrimitive()
{

}



void TextureDrawer3D::draw()
{
	ofSetColor(255);
	fboTexture3D.draw(drawingCanvasX + drawingCanvasSize + 10, drawingCanvasY);
	fboTexture3D.begin();
	drawBoiteDelimitation(ofPoint(64, 64, 0), 64, 64, 64);
	ofFill();
	ofSetColor(255, 255, 0);
	ofDrawCone(128, 128, 0, 100, 100);

	switch (objet3dTest1.type)
	{
	case GeometricRegularPrimitiveType::tetrahedron:
		ofFill();
		
		draw_tetrahedron();
		break;

	case GeometricRegularPrimitiveType::hexahedron:
		draw_hexahedron();
		break;

	case GeometricRegularPrimitiveType::octahedron:
		draw_octahedron();
		break;

	case GeometricRegularPrimitiveType::dodecahedron:
		draw_dodecahedron();
		break;

	case GeometricRegularPrimitiveType::icosahedron:
		draw_icosahedron();
		break;

	case GeometricRegularPrimitiveType::sphere:
		draw_sphere();
		break;

	default:
		break;
	}

	switch (objet3dTest2.type)
	{
	case GeometricOtherPrimitiveType::ellipse:
		draw_ellipse();
		break;

	case GeometricOtherPrimitiveType::polygon:
		draw_polygon();
		break;

	case GeometricOtherPrimitiveType::cylinder:
		draw_cylinder();
		break;

	case GeometricOtherPrimitiveType::rectangle:
		draw_rectangle();
		break;

	case GeometricOtherPrimitiveType::cone:
		draw_cone();
		break;

	default:
		break;
	}

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

void TextureDrawer3D::draw_tetrahedron() const
{
	
}

void TextureDrawer3D::draw_hexahedron() const
{

}

void TextureDrawer3D::draw_octahedron() const
{

}

void TextureDrawer3D::draw_dodecahedron() const
{

}

void TextureDrawer3D::draw_icosahedron() const
{

}

void TextureDrawer3D::draw_sphere() const
{

}

void TextureDrawer3D::draw_ellipse() const
{

}

void TextureDrawer3D::draw_polygon() const
{

}

void TextureDrawer3D::draw_cylinder() const
{

}

void TextureDrawer3D::draw_rectangle() const
{

}

void TextureDrawer3D::draw_cone() const
{

}


void TextureDrawer3D::updateColors(ofColor stroke, ofColor fill)
{
	geometricPrimitiveStrokeColor_r = stroke.r;
	geometricPrimitiveStrokeColor_g = stroke.g;
	geometricPrimitiveStrokeColor_b = stroke.b;
	geometricPrimitiveStrokeColor_a = stroke.a;

	geometricPrimitiveStrokeColor_r = fill.r;
	geometricPrimitiveStrokeColor_g = fill.g;
	geometricPrimitiveStrokeColor_b = fill.b;
	geometricPrimitiveStrokeColor_a = fill.a;
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