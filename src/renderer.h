#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "fileManager.h"
#include "cursor.h"

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
	void drawCursor();

private:
	FileManager fileManager;

	ofxPanel gui;
	ofxButton exportButton;
	void exportButtonPressed();
};