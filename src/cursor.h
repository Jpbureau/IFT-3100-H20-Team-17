#pragma once
#include "ofMain.h"
#include "textureDrawer.h"

enum CursorTypes
{
	none,
	pencil,
	hand
};

class Cursor
{
public:
	Cursor(TextureDrawer& textureDrawer);

	void setup();
	void setCursorImage(CursorTypes type);
	void draw();
	void update();

private:
	int x;
	int y;

	void mouseMoved(ofMouseEventArgs & mouse);

	ofImage pencilImage;
	ofImage handImage;
	CursorTypes type;

	TextureDrawer& textureDrawer;
};

