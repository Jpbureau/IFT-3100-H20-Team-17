#pragma once
#include "ofMain.h"

enum CursorTypes
{
	pencil,
	hand,
	none
};

class Cursor
{
public:
	void setup(int drawingCanvasX, int drawingCanvasY, int drawingCanvasSize);
	void setCursorImage(CursorTypes type);
	void draw();
	void update();
	void setPosition(int x, int y);

private:
	int x;
	int y;

	int drawingCanvasSize;
	int drawingCanvasX;
	int drawingCanvasY;

	ofImage pencilImage;
	ofImage handImage;
	CursorTypes type;

	bool isCursorInDrawingCanvas();
};
