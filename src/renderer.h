#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "fileManagerGui.h"
#include "cursor.h"
#include "textureDrawer.h"
#include "canvasGui.h"
#include "colorHistogramGui.h"
#include "colorHistogram.h"
#include "ofxAssimpModelLoader.h"
#include "ofPoint.h"
#include "canvas3DGui.h"
#include "ofVbo.h"
//#include <vector>

enum class MeshRenderMode { fill, wireframe, vertex };

class Renderer
{
public:
	void setup();
	void update();
	void draw();

	const int drawingCanvasSize = 600;
	int drawingCanvasX = 225;
	int drawingCanvasY = ofGetHeight() / 3.5;

	ofFbo fboTexture;
	ofFbo fboTexture3D;

	int mousePosX;
	int mousePosY;
	Cursor cursor;
	

	void mousePressed(int x, int y);
	void mouseReleased(int x, int y);

	void drawBoiteDelimitation(ofPoint point, float width, float height, float depth);

private:
	ofImage image;

	FileManagerGui fileManagerGui;

	TextureDrawer textureDrawer;
	CanvasGui canvas2dGui = CanvasGui(textureDrawer);

	Canvas3DGui canvas3DGui = Canvas3DGui();

	ColorHistogram colorHistogram;
	ColorHistogramGui colorHistogramGui = ColorHistogramGui(colorHistogram);

	ofxAssimpModelLoader teapot;
	ofxAssimpMeshHelper & meshHelper = teapot.getMeshHelper(0);
	ofVbo vbo;

	MeshRenderMode mesh_render_mode;

	ofLight light;

	ofMesh mesh;

	void calculerBoiteDelimitation();

	ofPoint pointSupGaucheBoite;
	int largeurModel3D;
	int hauteurModel3D;
	int profondeurModel3D;
};