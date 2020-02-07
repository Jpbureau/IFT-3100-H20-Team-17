#include "cursor.h"

void Cursor::setup()
{
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
		ofShowCursor;
	default:
		break;
	}
}

void Cursor::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
