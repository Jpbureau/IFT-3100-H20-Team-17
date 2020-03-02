#include "cursor.h"

Cursor::Cursor(TextureDrawer & textureDrawer):
	textureDrawer(textureDrawer)
{
}

void Cursor::setup()
{
	ofAddListener(ofEvents().mouseMoved, this, &Cursor::mouseMoved);
	ofAddListener(ofEvents().mouseDragged, this, &Cursor::mouseMoved);
	//ofAddListener(ofEvents().mousePressed, this, &Cursor::mouseMoved);
	//ofAddListener(ofEvents().mouseReleased, this, &Cursor::mouseMoved);

	pencilImage.load("cursor/pencil.png");
	handImage.load("cursor/hand.png");
}

void Cursor::setCursorImage(CursorTypes type)
{
	this->type = type;
}

void Cursor::draw()
{
	switch (type)
	{
	case pencil:
		ofHideCursor();
		pencilImage.draw(x, y - 30, 30, 30);
		break;
	case hand:
		ofHideCursor();
		handImage.draw(x, y - 30, 30, 30);
		break;
	case none:
		ofShowCursor();
		break;
	default:
		break;
	}
}

void Cursor::update()
{
	if (textureDrawer.isMouseInsideCanvas(x, y)) {
		setCursorImage(pencil);
	}
	else {
		setCursorImage(none);
	}
}

void Cursor::mouseMoved(ofMouseEventArgs & mouse)
{
	x = mouse.x;
	y = mouse.y;
}
