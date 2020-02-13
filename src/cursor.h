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
	void setup();
	void setCursorImage(CursorTypes type);
	void draw();
	void setPosition(int x, int y);

private:
	int x;
	int y;
	ofImage pencilImage;
	ofImage handImage;
	CursorTypes type;
};

