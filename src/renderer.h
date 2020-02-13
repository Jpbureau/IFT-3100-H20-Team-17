#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "fileManager.h"
#include "cursor.h"
#include "textureDrawer.h"

class Renderer
{
public:
	void setup();
	void draw();

	int canvasSize;
	int canvasPositionX;
	int canvasPositionY;

	int mousePosX;
	int mousePosY;
	Cursor cursor;
	TextureDrawer textureDrawer;
	void drawCursor();

	void mousePressed(int x, int y);
	void mouseReleased(int x, int y);

private:
	ofImage image;

	FileManager fileManager;

	ofxPanel menuPanel;
	ofxPanel drawingOptionsPanel;

	ofxButton drawLineButton;
	ofxButton drawPointButton;
	ofxButton drawRectangleButton;
	ofxButton drawEllipseButton;

	ofxButton importButton;
	void importButton_pressed();

	ofxButton exportButton;
	void exportButtonPressed();

	void selectPointType();
	void selectLineType();
	void selectRectangleType();
	void selectEllipseType();
};