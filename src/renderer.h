#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "fileManagerGui.h"
#include "cursor.h"
#include "textureDrawer.h"
#include "canvasGui.h"

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

	int mousePosX;
	int mousePosY;
	Cursor cursor;
	

	void mousePressed(int x, int y);
	void mouseReleased(int x, int y);

private:
	ofImage image;

	FileManagerGui fileManagerGui;

	TextureDrawer textureDrawer;
	CanvasGui canvas2dGui = CanvasGui(textureDrawer);
};