#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include <vector>


enum class ShaderType { none, lambert };

enum class GeometricRegularPrimitiveType { none, tetrahedron, hexahedron, octahedron, dodecahedron, icosahedron, sphere };
enum class GeometricOtherPrimitiveType { none, ellipse, polygon, cylinder, rectangle, cone};

struct VectorRegularGeometricPrimitive
{
	GeometricRegularPrimitiveType type;
	GLfloat                position[3];
	float                  stroke_width;
	GLubyte				   stroke_color[4];
	GLubyte                fill_color[4];
	GLfloat				   radius;
	bool				   selected;
};

struct VectorOtherGeometricPrimitive
{
	GeometricOtherPrimitiveType type;
	GLfloat                position[3];
	float                  stroke_width;
	GLubyte				   stroke_color[4];
	GLubyte                fill_color[4];
	GLfloat				   heigth;
	GLfloat				   width;
	GLfloat				   depth;
	GLubyte                nbSides;
	bool				   selected;
};


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

	void selectTetrahedronType();
	void selectHexahedronType();
	void selectOctahedronType();
	void selectDodecahedronType();
	void selectIcosahedronType();
	void selectSphereType();
	void selectEllipseType();
	void selectPolygonType();
	void selectCylinderType();
	void selectRectangleType();
	void selectConeType();


	void addGeometricPrimitive();

	void updateColors(ofColor stroke, ofColor fill);
	void updateCoordinates(GLfloat x, GLfloat y, GLfloat z);
	void updateRadius(float newRadius);
	void updateDimensions(GLfloat width, GLfloat height, GLfloat depth);
	void updateNbSides(GLubyte nbSides);

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

	VectorRegularGeometricPrimitive geometricRegularPrimitive;
	GeometricRegularPrimitiveType geometricRegularPrimitiveSelectedType;

	VectorOtherGeometricPrimitive geometricOtherPrimitive;
	GeometricOtherPrimitiveType geometricOtherPrimitiveSelectedType;

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

	float stroke_width;
	float radius;

	float geometricPrimitiveStroke_width;

	GLfloat geometricPrimitiveRadius;
	GLfloat geometricPrimitiveHeight;
	GLfloat geometricPrimitiveWidth;
	GLfloat geometricPrimitiveDepth;

	GLfloat geometricPrimitiveXCoordinate;
	GLfloat geometricPrimitiveYCoordinate;
	GLfloat geometricPrimitiveZCoordinate;

	GLubyte geometricPrimitiveNbSides;

	unsigned char geometricPrimitiveStrokeColor_r;
	unsigned char geometricPrimitiveStrokeColor_g;
	unsigned char geometricPrimitiveStrokeColor_b;
	unsigned char geometricPrimitiveStrokeColor_a;

	unsigned char geometricPrimitiveFillColor_r;
	unsigned char geometricPrimitiveFillColor_g;
	unsigned char geometricPrimitiveFillColor_b;
	unsigned char geometricPrimitiveFillColor_a;

	void draw_tetrahedron(GLfloat radius, GLfloat x, GLfloat y, GLfloat z) const;
	void draw_hexahedron(GLfloat radius, GLfloat x, GLfloat y, GLfloat z) const;
	void draw_octahedron(GLfloat radius, GLfloat x, GLfloat y, GLfloat z) const;
	void draw_dodecahedron(GLfloat radius, GLfloat x, GLfloat y, GLfloat z) const;
	void draw_icosahedron(GLfloat radius, GLfloat x, GLfloat y, GLfloat z) const;
	void draw_sphere(GLfloat radius, GLfloat x, GLfloat y, GLfloat z) const;
	void draw_ellipse(GLfloat width, GLfloat height, GLfloat depth, GLfloat x, GLfloat y, GLfloat z) const;
	void draw_polygon(GLfloat width, GLfloat height, GLfloat depth, GLfloat x, GLfloat y, GLfloat z, GLubyte nbSides) const;
	void draw_cylinder(GLfloat width, GLfloat height, GLfloat depth, GLfloat x, GLfloat y, GLfloat z) const;
	void draw_rectangle(GLfloat width, GLfloat height, GLfloat depth, GLfloat x, GLfloat y, GLfloat z) const;
	void draw_cone(GLfloat width, GLfloat height, GLfloat depth, GLfloat x, GLfloat y, GLfloat z) const;

};
