#pragma once
#include "ofMain.h"
#include "textureDrawer.h"
#include "textureDrawer3D.h"

enum CursorTypes
{
	none,
	pencil,
	hand,
	closedHand,
	selection
};

class Cursor
{
public:
	Cursor(TextureDrawer& textureDrawer, TextureDrawer3D& textureDrawer3D);

	void setup();
	void setCursorImage(CursorTypes type);
	void draw();
	void update();

private:
	int x;
	int y;

	void mouseMoved(ofMouseEventArgs & mouse);
	void mouseReleased(ofMouseEventArgs & mouse);
	void mousePressed(ofMouseEventArgs & mouse);

	ofImage pencilImage;
	ofImage handImage;
	ofImage closedHandImage;
	ofImage selectionCursorImage;

	CursorTypes type;

	bool mouseIsPressed;

	TextureDrawer& textureDrawer;
	TextureDrawer3D& textureDrawer3D;
};

