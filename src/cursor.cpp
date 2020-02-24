#include "cursor.h"

void Cursor::setup(int drawingCanvasX, int drawingCanvasY, int drawingCanvasSize)
{
	this->drawingCanvasX = drawingCanvasX;
	this->drawingCanvasY = drawingCanvasY;
	this->drawingCanvasSize = drawingCanvasSize;
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
	if (isCursorInDrawingCanvas()) {
		setCursorImage(pencil);
	}
	else {
		setCursorImage(none);
	}
}

bool Cursor::isCursorInDrawingCanvas()
{
	return x >= drawingCanvasX && x <= (drawingCanvasX + drawingCanvasSize) &&
		y >= drawingCanvasY && y <= (drawingCanvasY + drawingCanvasSize);
}


void Cursor::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
